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
(int l_id, std::string last_name, std::string first_name,
 std::string birthday, std::string phone_num, std::string e_mail_addr){
  if(c_dao->put(l_id, last_name, first_name, birthday, phone_num, e_mail_addr))return true;
  else return false;
}

LoginInfo Manager::fetch_Linfo_by_login
(std::string login){
  LoginInfo login_info_from_db = LoginInfo();
  if (l_dao->fetch("login='"+login+"'", login_info_from_db)){return login_info_from_db;}
  //else return login_info_from_db;
}

LoginInfo Manager::fetch_Linfo_by_l_id
(int l_id){
  LoginInfo login_info_from_db = LoginInfo();
  if (l_dao->fetch("id="+std::to_string(l_id), login_info_from_db)){return login_info_from_db;}
  //else return login_info_from_db;
}

CustomerInfo Manager::fetch_Cinfo_by_l_id
(int l_id){
  CustomerInfo cus_info_from_db = CustomerInfo();
  if (c_dao->fetch("l_id="+std::to_string(l_id), cus_info_from_db)){return cus_info_from_db;}
}

int main(){
  Manager m("db.conf");
  CustomerInfo c = CustomerInfo{};
  c = m.fetch_Cinfo_by_l_id(1);
  std::cout<<c.e_mail_addr<<std::endl;

  return 0;
}
