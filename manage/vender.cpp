#include "manage.h"

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
