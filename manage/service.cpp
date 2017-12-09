#include "manage.h"


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
