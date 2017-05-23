#ifndef __INCLUDED_DAO_H_
#define __INCLUDED_DAO_H_

#include <iostream>
#include <string>
#include <sstream>
#include <pqxx/pqxx>
#include <pqxx/except>
#include <memory>
#include <vector>
#include <cryptopp/osrng.h>
#include <iomanip>
#include <unistd.h>
//#include "type.h"
#include "sha256.h"

class DataBase{
  protected:
    std::unique_ptr<pqxx::connection> _conn;
    std::unique_ptr<pqxx::work> _T;

  public:
    DataBase(std::string, std::string, std::string);
    ~DataBase();
};

class LoginInfoDao: public DataBase{
  public:
    LoginInfoDao(std::string dbname, std::string user, std::string password);
    ~LoginInfoDao(){};
    bool put(std::string login, std::string hasded_pass, std::string salt);

};

#endif
