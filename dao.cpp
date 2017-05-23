#include "dao.h"

//===========class Database===========

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
}
