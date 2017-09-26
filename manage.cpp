#include "manage.h"

//==========LoginManager===========
LoginManager::LoginManager(std::string filename)
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

bool LoginManager::register_Linfo(
    std::string login,
    std::string password,
    USERTYPE user_type)
{
  std::string salt;
  salt=myhash::genSalt();
  std::string hashed_pass;
  hashed_pass=myhash::mySha256(password+salt);
  if(l_dao->put(login, hashed_pass, salt, user_type))return true;
  else return false;
}

LoginInfo LoginManager::fetch_Linfo_by_login(std::string login)
{
  LoginInfo login_info_from_db = LoginInfo();
  if (l_dao->fetch("login='"+login+"'", login_info_from_db)){return login_info_from_db;}
  //else return login_info_from_db;
}

LoginInfo LoginManager::fetch_Linfo_by_l_id(int l_id)
{
  LoginInfo login_info_from_db = LoginInfo();
  if (l_dao->fetch("id="+std::to_string(l_id), login_info_from_db)){return login_info_from_db;}
  else return login_info_from_db;
}

bool LoginManager::update_Linfo_by_l_id(int l_id, std::string set_attr){
  return l_dao->update(set_attr, "l_id = "+l_id);
}

//============CustomerManager============
CustomerManager::CustomerManager(std::string filename)
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

bool CustomerManager::register_Cinfo(
    int l_id,
    std::string last_name,
    std::string first_name,
    std::string birthday,
    std::string phone_num,
    std::string e_mail_addr)
{
  if(c_dao->put(l_id, last_name, first_name, birthday, phone_num, e_mail_addr))return true;
  else return false;
}

CustomerInfo CustomerManager::fetch_Cinfo_by_l_id(int l_id)
{
  CustomerInfo cus_info_from_db = CustomerInfo();
  if (c_dao->fetch("l_id="+std::to_string(l_id), cus_info_from_db)){return cus_info_from_db;}
  else return cus_info_from_db;
}

bool CustomerManager::update_Cinfo_by_c_id(int c_id, std::string set_attr){
  return c_dao->update(set_attr, "id = " + std::to_string(c_id));
}

//=========================================

//============VenderManager============
VenderManager::VenderManager(std::string filename)
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

bool VenderManager::register_Vinfo(
    int l_id,
    std::string name,
    std::string phone_num,
    std::string e_mail_addr)
{
  if(v_dao->put(l_id, name, phone_num, e_mail_addr))return true;
  else return false;
}

VenderInfo VenderManager::fetch_Vinfo_by_l_id(int l_id)
{
  VenderInfo ven_info_from_db = VenderInfo();
  if (v_dao->fetch("l_id="+std::to_string(l_id), ven_info_from_db)){return ven_info_from_db;}
  else return ven_info_from_db;
}

bool VenderManager::update_Vinfo_by_v_id(int v_id, std::string set_attr){
  return v_dao->update(set_attr, "id = " + std::to_string(v_id));
}
//=========================================
/*
int main(){
  CustomerManager c("db.conf");
  if(c.update_Cinfo_by_c_id(18, "first_name='ryo'"))std::cout<<"ok\n";
  else std::cout<<"out\n";
  return 0;
}
*/
