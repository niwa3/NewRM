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
  //_T.reset(new pqxx::work(*_conn.get()))
  
}

bool LoginInfoDao::put(std::string login, std::string hashed_pass, std::string salt){
  try{
    _T.reset(new pqxx::work(*_conn.get()));
    std::string INSERT_LOGIN_INFO;
    INSERT_LOGIN_INFO = "INSERT INTO login_info(login, passwd, salt) VALUES (" + _T.get()->quote(login) + "," + _T.get()->quote(hashed_pass)+ "," + _T.get()->quote(salt) + ");";
    _T.get()->exec(INSERT_LOGIN_INFO);
    _T.get()->commit();
    return true;
  }
  catch(const pqxx::pqxx_exception &e){
    std::cerr<<e.base().what()<<std::endl;
    return false;
  }
}
//====================================
int main(){
  LoginInfoDao login_db("test","testuser","testpass");
  std::string NAME;
  std::cout<< "Enter login ID: ";
  std::cin>> NAME;
  std::string PASS;
  PASS=getpass("Enter password: ");
  std::string salt;
  salt=myhash::genSalt();
  std::string hashed_pass;
  hashed_pass=myhash::mySha256(PASS+salt);

  login_db.put(NAME,hashed_pass,salt);

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
