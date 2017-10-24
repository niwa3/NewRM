#include "manage.h"

//==========LoginManageFuncs===========
LoginManageFuncs::LoginManageFuncs(std::string filename)
{
  std::ifstream db_conf(filename.c_str(), std::ios::in);
  std::string reading_line_buffer;
  std::vector<std::string> conf;
  std::string dbname;
  std::string user;
  std::string password;
  while(std::getline(db_conf, reading_line_buffer)){
    std::cout<<reading_line_buffer<<std::endl;
    std::string separated_string_buffer;
    std::istringstream line_separater(reading_line_buffer);
    while(std::getline(line_separater, separated_string_buffer, '=')){
      std::istringstream separated_word(separated_string_buffer);
      std::string tmp_conf;
      separated_word>>tmp_conf;
      conf.push_back(tmp_conf);
    }
  }
  for(std::vector<std::string>::iterator itr = conf.begin(); itr!=conf.end(); itr++){
    if(*itr=="dbname")dbname=*(itr+1);
    else if(*itr=="username")user=*(itr+1);
    else if(*itr=="password")password=*(itr+1);
  }

  l_dao.reset(new LoginInfoDao(dbname,user,password));
}


int LoginManageFuncs::register_Linfo(
    std::string login,
    std::string password,
    USERTYPE user_type)
{
  std::string salt;
  salt=myhash::genSalt();
  std::string hashed_pass;
  hashed_pass=myhash::mySha256(password+salt);
  return l_dao->put(login, hashed_pass, salt, user_type);
}


LoginInfo LoginManageFuncs::fetch_Linfo_by_login(std::string login)
{
  LoginInfo login_info_from_db = LoginInfo();
  if (l_dao->fetch("where login='"+login+"'", login_info_from_db)){return login_info_from_db;}
  else return login_info_from_db;
}


LoginInfo LoginManageFuncs::fetch_Linfo_by_l_id(int l_id)
{
  LoginInfo login_info_from_db = LoginInfo();
  if (l_dao->fetch("where id="+std::to_string(l_id), login_info_from_db)){return login_info_from_db;}
  else return login_info_from_db;
}


bool LoginManageFuncs::update_Linfo_by_l_id(int l_id, std::string set_attr){
  return l_dao->update(set_attr, "id = "+l_id);
}


bool LoginManageFuncs::delete_Linfo_by_l_id(int l_id){
  return l_dao->del("id = "+std::to_string(l_id));
}
//=======================================


//============CustomerManageFuncs============
CustomerManageFuncs::CustomerManageFuncs(std::string filename)
{
  std::ifstream db_conf(filename.c_str(), std::ios::in);
  std::string reading_line_buffer;
  std::vector<std::string> conf;
  std::string dbname;
  std::string user;
  std::string password;

  while(std::getline(db_conf, reading_line_buffer)){
    std::cout<<reading_line_buffer<<std::endl;
    std::string separated_string_buffer;
    std::istringstream line_separater(reading_line_buffer);
    while(std::getline(line_separater, separated_string_buffer, '=')){
      std::istringstream separated_word(separated_string_buffer);
      std::string tmp_conf;
      separated_word>>tmp_conf;
      conf.push_back(tmp_conf);
    }
  }

  for(std::vector<std::string>::iterator itr = conf.begin(); itr!=conf.end(); itr++){
    if(*itr=="dbname")dbname=*(itr+1);
    else if(*itr=="username")user=*(itr+1);
    else if(*itr=="password")password=*(itr+1);
  }

  c_dao.reset(new CustomerInfoDao(dbname,user,password));
}

int CustomerManageFuncs::register_Cinfo(
    int l_id,
    std::string last_name,
    std::string first_name,
    std::string birthday,
    std::string phone_num,
    std::string e_mail_addr)
{
  return c_dao->put(l_id, last_name, first_name, birthday, phone_num, e_mail_addr);
}

std::vector<CustomerInfo> CustomerManageFuncs::fetch_Cinfo_by_l_id(int l_id)
{
  std::vector<CustomerInfo> cus_info_from_db;
  if (c_dao->fetch("where l_id="+std::to_string(l_id), cus_info_from_db)){return cus_info_from_db;}
  else return cus_info_from_db;
}

bool CustomerManageFuncs::update_Cinfo_by_c_id(int c_id, std::string set_attr){
  return c_dao->update(set_attr, "id = " + std::to_string(c_id));
}

bool CustomerManageFuncs::delete_Cinfo_by_c_id(int c_id){
  return c_dao->del("id = "+std::to_string(c_id));
}
//=========================================

//============DeviceManageFuncs============
DeviceManageFuncs::DeviceManageFuncs(std::string filename)
{
  std::ifstream db_conf(filename.c_str(), std::ios::in);
  std::string reading_line_buffer;
  std::vector<std::string> conf;
  std::string dbname;
  std::string user;
  std::string password;

  while(std::getline(db_conf, reading_line_buffer)){
    std::cout<<reading_line_buffer<<std::endl;
    std::string separated_string_buffer;
    std::istringstream line_separater(reading_line_buffer);
    while(std::getline(line_separater, separated_string_buffer, '=')){
      std::istringstream separated_word(separated_string_buffer);
      std::string tmp_conf;
      separated_word>>tmp_conf;
      conf.push_back(tmp_conf);
    }
  }

  for(std::vector<std::string>::iterator itr = conf.begin(); itr!=conf.end(); itr++){
    if(*itr=="dbname")dbname=*(itr+1);
    else if(*itr=="username")user=*(itr+1);
    else if(*itr=="password")password=*(itr+1);
  }

  d_dao.reset(new DeviceInfoDao(dbname,user,password));
}

int DeviceManageFuncs::register_Dinfo(
    int c_id,
    std::string device_name,
    int default_privacy_standard,
    DEVICETYPE device_type,
    DATATYPE data_type,
    int interval,
    std::string location)
{
  return d_dao->put(c_id, device_name, default_privacy_standard, device_type, data_type, interval, location);
}

std::vector<DeviceInfo> DeviceManageFuncs::fetch_Dinfo_by_c_id(int c_id)
{
  std::vector<DeviceInfo> dev_info_from_db;
  if (d_dao->fetch("where c_id="+std::to_string(c_id), dev_info_from_db)){return dev_info_from_db;}
  else return dev_info_from_db;
}

DeviceInfo DeviceManageFuncs::fetch_Dinfo_by_d_id(int d_id)
{
  DeviceInfo dev_info_from_db;
  if (d_dao->fetch("where id="+std::to_string(d_id), dev_info_from_db)){return dev_info_from_db;}
  else return dev_info_from_db;
}

DeviceInfo DeviceManageFuncs::fetch_Dinfo_by_device_name(std::string device_name)
{
  DeviceInfo dev_info_from_db;
  if (d_dao->fetch("where device_name='"+device_name+"'", dev_info_from_db)){return dev_info_from_db;}
  else return dev_info_from_db;
}

std::vector<DeviceInfo> DeviceManageFuncs::fetch_Dinfo_for_matching(DATATYPE data_type, int privacy_standard, int interval)
{
  std::vector<DeviceInfo> dev_info_from_db;
  if (d_dao->fetch("where data_type="+std::to_string((int)data_type)+" and default_privacy_standard<="+std::to_string(privacy_standard)+" and interval<="+std::to_string(interval), dev_info_from_db)){return dev_info_from_db;}
  else return dev_info_from_db;
}


bool DeviceManageFuncs::update_Dinfo_by_d_id(int d_id, std::string set_attr){
  return d_dao->update(set_attr, "id = " + std::to_string(d_id));
}

bool DeviceManageFuncs::delete_Dinfo_by_d_id(int d_id){
  return d_dao->del("id = "+std::to_string(d_id));
}
//=========================================


//============VenderManageFuncs============
VenderManageFuncs::VenderManageFuncs(std::string filename)
{
  std::ifstream db_conf(filename.c_str(), std::ios::in);
  std::string reading_line_buffer;
  std::vector<std::string> conf;
  std::string dbname;
  std::string user;
  std::string password;
  while(std::getline(db_conf, reading_line_buffer)){
    std::cout<<reading_line_buffer<<std::endl;
    std::string separated_string_buffer;
    std::istringstream line_separater(reading_line_buffer);
    while(std::getline(line_separater, separated_string_buffer, '=')){
      std::istringstream separated_word(separated_string_buffer);
      std::string tmp_conf;
      separated_word>>tmp_conf;
      conf.push_back(tmp_conf);
    }
  }
  for(std::vector<std::string>::iterator itr = conf.begin(); itr!=conf.end(); itr++){
    if(*itr=="dbname")dbname=*(itr+1);
    else if(*itr=="username")user=*(itr+1);
    else if(*itr=="password")password=*(itr+1);
  }

  v_dao.reset(new VenderInfoDao(dbname,user,password));
}

int VenderManageFuncs::register_Vinfo(
    int l_id,
    std::string name,
    std::string phone_num,
    std::string e_mail_addr)
{
  return v_dao->put(l_id, name, phone_num, e_mail_addr);
}

std::vector<VenderInfo> VenderManageFuncs::fetch_Vinfo_by_l_id(int l_id)
{
  std::vector<VenderInfo> ven_info_from_db;
  if (v_dao->fetch("where l_id="+std::to_string(l_id), ven_info_from_db)){return ven_info_from_db;}
  else return ven_info_from_db;
}

bool VenderManageFuncs::update_Vinfo_by_v_id(int v_id, std::string set_attr){
  return v_dao->update(set_attr, "id = " + std::to_string(v_id));
}

bool VenderManageFuncs::delete_Vinfo_by_v_id(int v_id){
  return v_dao->del("id = "+std::to_string(v_id));
}
//=========================================

//============ServiceManageFuncs============
ServiceManageFuncs::ServiceManageFuncs(std::string filename)
{
  std::ifstream db_conf(filename.c_str(), std::ios::in);
  std::string reading_line_buffer;
  std::vector<std::string> conf;
  std::string dbname;
  std::string user;
  std::string password;

  while(std::getline(db_conf, reading_line_buffer)){
    std::cout<<reading_line_buffer<<std::endl;
    std::string separated_string_buffer;
    std::istringstream line_separater(reading_line_buffer);
    while(std::getline(line_separater, separated_string_buffer, '=')){
      std::istringstream separated_word(separated_string_buffer);
      std::string tmp_conf;
      separated_word>>tmp_conf;
      conf.push_back(tmp_conf);
    }
  }

  for(std::vector<std::string>::iterator itr = conf.begin(); itr!=conf.end(); itr++){
    if(*itr=="dbname")dbname=*(itr+1);
    else if(*itr=="username")user=*(itr+1);
    else if(*itr=="password")password=*(itr+1);
  }

  s_dao.reset(new ServiceInfoDao(dbname,user,password));
}

int ServiceManageFuncs::register_Sinfo(
    int v_id,
    std::string service_name,
    int required_privacy_standard,
    DATATYPE data_type,
    int interval)
{
  return s_dao->put(v_id, service_name, required_privacy_standard, data_type, interval);
}

std::vector<ServiceInfo> ServiceManageFuncs::fetch_Sinfo_by_v_id(int v_id)
{
  std::vector<ServiceInfo> ser_info_from_db;
  if (s_dao->fetch("where v_id="+std::to_string(v_id), ser_info_from_db)){return ser_info_from_db;}
  else return ser_info_from_db;
}

ServiceInfo ServiceManageFuncs::fetch_Sinfo_by_s_id(int s_id)
{
  ServiceInfo ser_info_from_db;
  if (s_dao->fetch("where id="+std::to_string(s_id), ser_info_from_db)){return ser_info_from_db;}
  else return ser_info_from_db;
}

ServiceInfo ServiceManageFuncs::fetch_Sinfo_by_service_name(std::string service_name)
{
  ServiceInfo ser_info_from_db;
  if (s_dao->fetch("where service_name='"+service_name+"'", ser_info_from_db)){return ser_info_from_db;}
  else return ser_info_from_db;
}


std::vector<ServiceInfo> ServiceManageFuncs::fetch_Sinfo_for_matching(DATATYPE data_type, int privacy_standard, int interval)
{
  std::vector<ServiceInfo> ser_info_from_db;
  if (s_dao->fetch("where data_type="+std::to_string((int)data_type)+" and required_privacy_standard>="+std::to_string(privacy_standard)+" and interval>="+std::to_string(interval), ser_info_from_db)){return ser_info_from_db;}
  else return ser_info_from_db;
}

bool ServiceManageFuncs::update_Sinfo_by_s_id(int s_id, std::string set_attr){
  return s_dao->update(set_attr, "id = " + std::to_string(s_id));
}

bool ServiceManageFuncs::delete_Sinfo_by_s_id(int s_id){
  return s_dao->del("id = "+std::to_string(s_id));
}
//=========================================


//==========RelationshipManageFuncs============
RelationshipManageFuncs::RelationshipManageFuncs(std::string filename)
{
  std::ifstream db_conf(filename.c_str(), std::ios::in);
  std::string reading_line_buffer;
  std::vector<std::string> conf;
  std::string dbname;
  std::string user;
  std::string password;

  while(std::getline(db_conf, reading_line_buffer)){
    std::cout<<reading_line_buffer<<std::endl;
    std::string separated_string_buffer;
    std::istringstream line_separater(reading_line_buffer);
    while(std::getline(line_separater, separated_string_buffer, '=')){
      std::istringstream separated_word(separated_string_buffer);
      std::string tmp_conf;
      separated_word>>tmp_conf;
      conf.push_back(tmp_conf);
    }
  }

  for(std::vector<std::string>::iterator itr = conf.begin(); itr!=conf.end(); itr++){
    if(*itr=="dbname")dbname=*(itr+1);
    else if(*itr=="username")user=*(itr+1);
    else if(*itr=="password")password=*(itr+1);
  }

  r_dao.reset(new RelationshipDao(dbname,user,password));
}

int RelationshipManageFuncs::register_Relation(
    int d_id,
    std::string device_name,
    int s_id,
    std::string service_name,
    ANONYMITYMETHOD anonymity_method,
    int privacy_standard,
    int interval,
    std::string location)
{
  return r_dao->put(d_id, device_name, s_id, service_name, anonymity_method, privacy_standard, interval, location);
}

std::vector<int> RelationshipManageFuncs::register_Relation(
    std::vector<Relationship> new_relationships)
{
  return r_dao->put_all(new_relationships);
}

std::vector<Relationship> RelationshipManageFuncs::fetch_Relation_by_d_id(int d_id)
{
  std::vector<Relationship> relation_from_db;
  r_dao->fetch("where d_id="+std::to_string(d_id), relation_from_db);
  return relation_from_db;
}

std::vector<Relationship> RelationshipManageFuncs::fetch_Relation_by_s_id(int s_id)
{
  std::vector<Relationship> relation_from_db;
  r_dao->fetch("where s_id="+std::to_string(s_id), relation_from_db);
  return relation_from_db;
}

std::vector<Relationship> RelationshipManageFuncs::fetch_Relation_by_c_id(int c_id)
{
  std::vector<Relationship> relation_from_db;
  std::string WHERE_JOIN = "INNER JOIN ( select distinct d.id from device_info d where d.c_id=" + std::to_string(c_id)+" ) t on r.d_id = t.id";
  if (r_dao->fetch(WHERE_JOIN, relation_from_db)){return relation_from_db;}
  else return relation_from_db;
}

std::vector<Relationship> RelationshipManageFuncs::fetch_Relation_by_v_id(int v_id)
{
  std::vector<Relationship> relation_from_db;
  std::string WHERE_JOIN = "INNER JOIN ( select distinct s.id from service_info s where s.v_id=" + std::to_string(v_id)+" ) t on r.s_id = t.id";
  if (r_dao->fetch(WHERE_JOIN, relation_from_db)){return relation_from_db;}
  else return relation_from_db;
}

bool RelationshipManageFuncs::update_Relation_by_r_id(int r_id, std::string set_attr){
  return r_dao->update(set_attr, "id = " + std::to_string(r_id));
}

bool RelationshipManageFuncs::delete_Relation_by_r_id(int r_id){
  return r_dao->del("id = "+std::to_string(r_id));
}

bool RelationshipManageFuncs::delete_Relation_by_d_id(int d_id){
  return r_dao->del("d_id = "+std::to_string(d_id));
}

bool RelationshipManageFuncs::delete_Relation_by_s_id(int s_id){
  return r_dao->del("s_id = "+std::to_string(s_id));
}
