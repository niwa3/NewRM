#include "manage.h"


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
