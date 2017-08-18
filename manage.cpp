#include "manage.h"

Manager::Manager
(std::string filename){
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
  c_dao.reset(new CustomerInfoDao(dbname,user,password));
}

bool Manager::register_Linfo
(std::string login, std::string password, USERTYPE user_type){
  std::string salt;
  salt=myhash::genSalt();
  std::string hashed_pass;
  hashed_pass=myhash::mySha256(password+salt);
  if(l_dao->put(login, hashed_pass, salt, user_type))return true;
  else return false;
}

bool Manager::register_Cinfo
(int l_id, std::string last_name, std::string first_name, std::string birthday, std::string phone_num, std::string e_mail_addr){
  if(c_dao->put(l_id, last_name, first_name, birthday, phone_num, e_mail_addr))return true;
  else return false;
}

bool Manage::register_Linfo
(std::string login, std::string password, USERTYPE user_type){
}
int main(){
  Manager m("db.conf");
  
  m.register_Linfo("pupupu", "hahahaha", USERTYPE::VENDER);
  m.register_Cinfo(12,"pu","ha","2013-01-01","09064445904","jfsljfal@klsjdfal");
  return 0;
}
