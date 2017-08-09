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
    info_from_db.user_id = itr_login_info["id"].as<int>();
    info_from_db.login = itr_login_info["login"].as<std::string>();
    info_from_db.salt = itr_login_info["salt"].as<std::string>();
    info_from_db.hashed_pass = itr_login_info["passwd"].as<std::string>();
    //std::stoi(itr_login_info["user_type"].as<std::string>()) == 0 ? (info_from_db.user_type = CUSTOMER) : (info_from_db.user_type = VENDER);
    itr_login_info["user_type"].as<int>() == 0 ? (info_from_db.user_type = CUSTOMER) : (info_from_db.user_type = VENDER);
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



//========class CustomerInfoDao=======
CustomerInfoDao::CustomerInfoDao(std::string dbname, std::string user, std::string password) : DataBase(dbname, user, password){
}

bool CustomerInfoDao::put(int l_id, std::string last_name, std::string first_name, std::string birthday, unsigned int phone_num, std::string e_mail_addr){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string INSERT_CUSTOMER_INFO;
    INSERT_CUSTOMER_INFO = "INSERT INTO customer_info"
      "(l_id, last_name, first_name, birthday, phone_num, e_mail_addr)"
      " VALUES (" + std::to_string(l_id) + 
      "," + _T.get()->quote(last_name) + 
      "," + _T.get()->quote(first_name) + 
      ", " + _T.get()->quote(birthday) + 
      "," + _T.get()->quote(std::to_string(phone_num)) + 
      "," + _T.get()->quote(e_mail_addr) + 
      ");";
    _T.get()->exec(INSERT_CUSTOMER_INFO);
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}

bool CustomerInfoDao::fetch(int l_id, CustomerInfo &customer_info_from_db){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string SELECT_CUSTOMER_INFO;
    SELECT_CUSTOMER_INFO = "SELECT id, l_id, last_name, first_name, birthday, phone_num, e_mail_addr FROM customer_info WHERE l_id=" + std::to_string(l_id) + ";";
    pqxx::result result_from_db;
    result_from_db =_T.get()->exec(SELECT_CUSTOMER_INFO);
    if(result_from_db.empty()){
      std::cerr<<"no customer info\n";
      return false;
    }
    pqxx::result::iterator itr_result_info;
    itr_result_info = result_from_db.begin();
    customer_info_from_db.l_id = itr_result_info["l_id"].as<int>();
    customer_info_from_db.c_id = itr_result_info["id"].as<int>();
    customer_info_from_db.last_name = itr_result_info["last_name"].as<std::string>();
    customer_info_from_db.first_name = itr_result_info["first_name"].as<std::string>();
    customer_info_from_db.birthday = itr_result_info["birthday"].as<std::string>();
    customer_info_from_db.phone_num = itr_result_info["phone_num"].as<long>();
    customer_info_from_db.e_mail_addr = itr_result_info["e_mail_addr"].as<std::string>();
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
  CustomerInfoDao customer_db("test","testuser","testpass");
  char menu;
  std::cout<<"MENU\n";
  std::cout<<"a. register your account\n";
  std::cout<<"b. login\n";
  std::cout<<"c. change password\n";
  std::cout<<"d. change login\n";
  std::cout<<"e. put customerinfo\n";
  std::cout<<"f. fetch customerinfo\n";
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
                std::cout<< "Customer of Vender (please enter 'c' or 'v'): ";
                std::cin>> con_type;
                if(con_type=='c')
                  login_db.put(NAME,hashed_pass,salt, CUSTOMER);
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
                  info_from_db.user_type == CUSTOMER ? (std::cout<<"a customer."<<std::endl) : (std::cout<<"a vender."<<std::endl);
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
    case 'e':{
               std::cout<<"Enter your l_id: ";
               int l_id;
               std::cin>> l_id;
               std::cout<<"Enter your first name: ";
               std::string first_name;
               std::cin>> first_name;
               std::cout<<"Enter your last name: ";
               std::string last_name;
               std::cin>> last_name;
               std::cout<<"Enter your birthday\nMonth(1-12): ";
               std::string birthday;
               int mon;
               std::cin>> mon;
               std::cout<<"Day(1-31): ";
               int day;
               std::cin>> day;
               std::cout<<"Year: ";
               int year;
               std::cin>> year;
               birthday=std::to_string(year)+"-"+std::to_string(mon)+"-"+std::to_string(day);
               std::cout<<"Enter your phone number: ";
               unsigned int phone_num;
               std::cin>> phone_num;
               std::cout<<"Enter your e mail addres: ";
               std::string e_mail_addr;
               std::cin>> e_mail_addr;

               std::cout<<"Registering\n";

               customer_db.put(l_id,last_name,first_name,birthday,phone_num,e_mail_addr);
               std::cout<<"ok\n";
               break;
             }
    case 'f':{
               std::cout<<"Enter your longin id: ";
               int l_id;
               std::cin>> l_id;
               CustomerInfo c_info;
               customer_db.fetch(l_id, c_info);
               std::cout<<c_info.c_id<<c_info.last_name<<c_info.first_name<<c_info.birthday<<c_info.phone_num<<c_info.e_mail_addr<<std::endl;
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
