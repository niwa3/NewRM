#include "dao.h"


//===========class DataBase===========
DataBase::DataBase(std::string dbname, std::string user, std::string password){
  try{
  std::string CONNECT_CONF="dbname='"+dbname+"' user='"+user+"' password='"+password+"'";
  _conn.reset(new pqxx::connection(CONNECT_CONF));
  if(_conn.get()->is_open()){
      std::cout<<"Database "<<_conn.get()->dbname()<<" opened." <<std::endl;
  }
  }catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
  }
}

DataBase::~DataBase(){ 
  if(_conn){
    if(_conn.get()->is_open()) _conn.get()->disconnect();
  }
}
//====================================



//===========class LoginInfoDao=======
LoginInfoDao::LoginInfoDao(std::string dbname, std::string user, std::string password) : DataBase(dbname, user, password){
}

bool LoginInfoDao::put(std::string login, std::string hashed_pass, std::string salt, USERTYPE user_type){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string INSERT_LOGIN_INFO;
    INSERT_LOGIN_INFO = "INSERT INTO login_info(login, passwd, salt, user_type) VALUES (" + _T.get()->quote(login) + "," + _T.get()->quote(hashed_pass)+ "," + _T.get()->quote(salt) + ", " + std::to_string(user_type) + ");";
    _T.get()->exec(INSERT_LOGIN_INFO);
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}

bool LoginInfoDao::fetch(std::string login, LoginInfo &info_from_db){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string SELECT_LOGIN_INFO;
    SELECT_LOGIN_INFO = "SELECT id, login, passwd, salt, user_type FROM login_info WHERE login=" + _T.get()->quote(login) + ";";
    pqxx::result login_info_from_db;
    login_info_from_db=_T.get()->exec(SELECT_LOGIN_INFO);
    if(login_info_from_db.empty()){
      std::cerr<<"the login ID: " + login + " does not exist.\n";
      return false;
    }
    pqxx::result::iterator itr_login_info;
    itr_login_info = login_info_from_db.begin();
    info_from_db.user_id = itr_login_info["id"].as<std::string>();
    info_from_db.login = itr_login_info["login"].as<std::string>();
    info_from_db.salt = itr_login_info["salt"].as<std::string>();
    info_from_db.hashed_pass = itr_login_info["passwd"].as<std::string>();
    //std::stoi(itr_login_info["user_type"].as<std::string>()) == 0 ? (info_from_db.user_type = CONSUMER) : (info_from_db.user_type = VENDER);
    itr_login_info["user_type"].as<int>() == 0 ? (info_from_db.user_type = CONSUMER) : (info_from_db.user_type = VENDER);
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}

bool LoginInfoDao::update_pass(std::string login, std::string hashed_new_pass, std::string new_salt){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string UPDATE_PASSWORD;
    UPDATE_PASSWORD = "UPDATE login_info SET passwd=" + _T.get()->quote(hashed_new_pass) + ", salt=" + _T.get()->quote(new_salt) + " WHERE login=" + _T.get()->quote(login) + ";";
    _T.get()->exec(UPDATE_PASSWORD);
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}

bool LoginInfoDao::update_login(std::string login, std::string new_login){
   try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string UPDATE_LOGIN;
    UPDATE_LOGIN = "UPDATE login_info SET login=" + _T.get()->quote(new_login) + " WHERE login=" + _T.get()->quote(login) + ";";
    _T.get()->exec(UPDATE_LOGIN);
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}
//====================================



//========class ConsumerInfoDao=======
ConsumerInfoDao::ConsumerInfoDao(std::string dbname, std::string user, std::string password) : DataBase(dbname, user, password){
}

bool ConsumerInfoDao::put(std::string l_id, std::string c_id, std::string last_name, std::string first_name, std::tm birthday, int phone_num, std::string e_mail_addr){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string INSERT_CONSUMER_INFO;
    INSERT_CONSUMER_INFO = "INSERT INTO consumer_info"
      "(l_id, last_name, first_name, birthday, phone_num, e_mail_addr)"
      " VALUES (" + _T.get()->quote(l_id) + 
      "," + _T.get()->quote(last_name)+ 
      "," + _T.get()->quote(first_name) + 
      ", " + _T.get()->quote(std::ctime(birthday)) + 
      "," + std::to_string(phone_num) + 
      "," + _T.get()->quote(e_mail_addr) + 
      ");";
    _T.get()->exec(INSERT_CONSUMER_INFO);
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}

bool ConsumerInfoDao::fetch(std::string l_id, ConsumerInfo &consumer_info_from_db){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string SELECT_CONSUMER_INFO;
    SELECT_CONSUMER_INFO = "SELECT id, l_id, last_name, first_name, birthday, phone_num, e_mail_addr FROM consumer_info WHERE login=" + _T.get()->quote(login) + ";";
    //whereの条件どうしよ
    pqxx::result login_info_from_db;
    login_info_from_db=_T.get()->exec(SELECT_CONSUMER_INFO);
    if(login_info_from_db.empty()){
      std::cerr<<"the login ID: " + login + " does not exist.\n";
      return false;
    }
    pqxx::result::iterator itr_login_info;
    itr_login_info = login_info_from_db.begin();
    info_from_db.user_id = itr_login_info["id"].as<std::string>();
    info_from_db.login = itr_login_info["login"].as<std::string>();
    info_from_db.salt = itr_login_info["salt"].as<std::string>();
    info_from_db.hashed_pass = itr_login_info["passwd"].as<std::string>();
    //std::stoi(itr_login_info["user_type"].as<std::string>()) == 0 ? (info_from_db.user_type = CONSUMER) : (info_from_db.user_type = VENDER);
    itr_login_info["user_type"].as<int>() == 0 ? (info_from_db.user_type = CONSUMER) : (info_from_db.user_type = VENDER);
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
};
//====================================
int main(){
  LoginInfoDao login_db("test","testuser","testpass");
  char menu;
  std::cout<<"MENU\n";
  std::cout<<"a. register your account\n";
  std::cout<<"b. login\n";
  std::cout<<"c. change password\n";
  std::cout<<"d. change login\n";
  std::cout<<"Enter a menu char: ";
  std::cin>> menu;
  std::string NAME;
  std::string PASS;
  switch(menu){
    case 'a':{
      std::cout<< "Enter new login ID: ";
      std::cin>> NAME;
      PASS=getpass("Enter new password: ");
      std::string salt;
      salt=myhash::genSalt();
      std::string hashed_pass;
      hashed_pass=myhash::mySha256(PASS+salt);
      char con_type;
      std::cout<< "Consumer of Vender (please enter 'c' or 'v'): ";
      std::cin>> con_type;
      if(con_type=='c')
        login_db.put(NAME,hashed_pass,salt, CONSUMER);
      else
        login_db.put(NAME,hashed_pass,salt, VENDER);
      break;
             }
    case 'b':{
      std::cout<< "Enter your login ID: ";
      std::cin>> NAME;
      LoginInfo info_from_db;
      if(!login_db.fetch(NAME, info_from_db)){
        break;
      }
      PASS=getpass("Enter your password: ");
      std::string hashed_in_pass;
      hashed_in_pass = myhash::mySha256(PASS+info_from_db.salt);
      if(hashed_in_pass == info_from_db.hashed_pass){
        std::cout<<"Hello, "<<info_from_db.login<<"!"<<std::endl;
        std::cout<<"You are ";
        info_from_db.user_type == CONSUMER ? (std::cout<<"a consumer."<<std::endl) : (std::cout<<"a vender."<<std::endl);
      }
      else{
        std::cerr<<"invalid password\n";
      }
      break;
             }
    case 'c':{
      std::cout<< "Enter your login ID: ";
      std::cin>> NAME;
      PASS=getpass("Enter new password: ");
      std::string new_salt;
      new_salt=myhash::genSalt();
      std::string hashed_new_pass;
      hashed_new_pass=myhash::mySha256(PASS+new_salt);
      login_db.update_pass(NAME,hashed_new_pass,new_salt);
      break;
             }
    case 'd':{
      std::cout<< "Enter your login ID: ";
      std::cin>> NAME;
      std::string new_login;
      std::cout<< "Enter new login ID: ";
      std::cin>> new_login;
      login_db.update_login(NAME,new_login);
      break;
             }
   default:
      break;
  }
  return 0;
}

/*
int main(){
  try{
    std::unique_ptr<pqxx::connection> conn(new pqxx::connection("dbname='test' user='testuser' password='testpass'"));
    if(conn.get()->is_open()){
      std::cout<<"Database "<<conn.get()->dbname()<<" opened." <<std::endl;
    }
    else{
      std::cout<<"Cannot Open Database."<<std::endl;
      return 1;
    }
    std::string NAME;
    std::cout<< "Enter login ID: ";
    std::cin>> NAME;
    std::cout<< std::endl;
    std::string PASS;
    PASS=getpass("Enter password: ");

    std::string QUERY;
    std::string salt;
    salt=myhash::genSalt();
    std::string hashPass;
    hashPass=myhash::mySha256(PASS+salt);

    std::unique_ptr<pqxx::work> T(new pqxx::work(*conn.get()));
    QUERY = "INSERT INTO login_info(login, passwd, salt) VALUES (" + T.get()->quote(NAME) + "," + T.get()->quote(hashPass)+ "," + T.get()->quote(salt) + ");";
    pqxx::result result = T.get()->exec("select relname from pg_stat_user_tables where relname = 'login_info'");
    if(result.empty()){
      T.get()->exec("CREATE TABLE login_info(id serial primary key not null, created_at timestamp not null default current_timestamp,updated_at timestamp not null default current_timestamp, login varchar(64) not null unique, passwd varchar(64) not null, salt varchar(64) not null)");
    }

    T.get()->exec(QUERY);
    T.get()->commit();

    T.reset(new pqxx::work(*conn.get()));

    std::cout<< "Enter login ID: ";
    std::cin>> NAME;
    std::cout<< std::endl;
    PASS.clear();
    PASS=getpass("Enter password: ");
    std::cout<< std::endl;

    QUERY.clear();
    QUERY = "SELECT login,salt,passwd FROM login_info WHERE login=" + T.get()->quote(NAME) + ";";
    std::cout<<QUERY<<std::endl;
    result = T.get()->exec(QUERY);
    pqxx::result::iterator result_itr;
    result_itr = result.begin();
    salt = result_itr["salt"].as<std::string>();
    hashPass = myhash::mySha256(PASS+salt);
    if(hashPass == result_itr["passwd"].as<std::string>()){
      std::cout<<result_itr["login"].as<std::string>()<<std::endl;
    }
    else{
      std::cout<<"error";
    }
    T.get()->commit();

    conn.get()->disconnect();
    }
  catch(const std::exception &e){
    std::cerr<<e.what();
    return 1;
  }
  return 0;
}*/
