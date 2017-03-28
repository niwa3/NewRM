#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <vector>

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
    int NAME;
    std::cout<< "Enter Integer ID: ";
    std::cin>> NAME;
    std::cout<< std::endl;
    double VALUE;
    std::cout<<"Enter Double Value: ";
    std::cin >> VALUE;

    std::string QUERY;

    QUERY = "INSERT INTO cpptest VALUES (" + std::to_string(NAME) + "," + std::to_string(VALUE)+ ");";
    std::unique_ptr<pqxx::work> T(new pqxx::work(*conn.get()));
    pqxx::result result = T.get()->exec("select relname from pg_stat_user_tables where relname = 'cpptest'");
    if(result.empty()){
      T.get()->exec("CREATE TABLE cpptest(NAME integer, VALUS double precision)");
    }

    T.get()->exec(QUERY);
    T.get()->commit();
    conn.get()->disconnect();
    }
  catch(const std::exception &e){
    std::cerr<<e.what();
    return 1;
  }
  return 0;
}
