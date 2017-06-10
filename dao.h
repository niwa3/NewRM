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
#include <unkstd.h>
#include <ctime>
//#include "type.h"
#include "sha256.h"

enum USERTYPE { CONSUMER, VENDER };

class LoginInfo{
  public:
    std::string login;
    std::string hashed_pass;
    std::string salt;
    std::string user_id;
    USERTYPE    user_type;
};

class ConsumerInfo{
  public:
    std::string l_id;
    std::string c_id;
    std::string last_name;
    std::string first_name;
    std::tm     birthday;
    int         phone_num;
    std::string e_mail_addr;
};

class DataBase{
  protected:
    std::unique_ptr<pqxx::connection> _conn;
    std::unique_ptr<pqxx::work> _T;

  public:
    DataBase(std::string, std::string, std::string);
    ~DataBase();
};

/*
 *ログイン用の情報にアクセス
 *属性：
 *id
 *login
 *hashed_pass
 *slat
 *user_type
 */
class LoginInfoDao: public DataBase{
  public:
    LoginInfoDao(std::string dbname, std::string user, std::string password);
    ~LoginInfoDao(){};
    bool put(std::string login, std::string hashed_pass, std::string salt, USERTYPE user_type );
    bool fetch(std::string login, LoginInfo &log_info_from_db);
    bool update_pass(std::string login, std::string hashed_new_pass, std::string new_salt);
    bool update_login(std::string login, std::string new_login);
};

/*
 *コンシューマの情報にアクセス
 *属性：
 *l_id 
 *id
 *last_name
 *first_name
 *birthday
 *phone_num
 *e_mail_addr
 *
 *
 */
class ConsumerInfoDao: public DataBase{
  public:
    ConsumerInfoDao(std::string dbname, std::string user, std::string password);
    ~ConsumerInfoDao(){};
    bool put(std::string l_id, std::string c_id, std::string last_name, std::string first_name, std::tm birthday, int phone_num, std::string e_mail_addr);
    bool fetch(std::string l_id, ConsumerInfo &consumer_info_from_db);
    bool update_name(std::string c_id, std::string last_name, std::string first_name){};
    bool update_e_mail(std::string c_id, std::string e_mail_addr){};
};

#endif
