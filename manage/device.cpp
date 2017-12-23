#include "manage.h"

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


std::vector<int> DeviceManageFuncs::register_Dinfo(std::vector<DeviceInfo> vec_device)
{
  return d_dao->put(vec_device);
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


