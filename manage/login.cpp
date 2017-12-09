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
