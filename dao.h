#ifndef __INCLUDED_DAO_H__
#define __INCLUDED_DAO_H__

#include <iostream>
#include <string>
#include <sstream>
#include <pqxx/pqxx>
#include <pqxx/except>
#include <memory>
#include <vector>
#include <unistd.h>
#include <cryptopp/osrng.h>
#include <iomanip>
#include <ctime>
//#include "type.h"
#include "sha256.h"

enum USERTYPE { CUSTOMER, VENDER, NONE };

class LoginInfo{
  public:
    LoginInfo(){
      this->login = {0};
      this->hashed_pass = {0};
      this->salt = {0};
      this->user_id = 0;
      this->user_type = USERTYPE::NONE;
    }
    std::string login;
    std::string hashed_pass;
    std::string salt;
    int user_id;
    USERTYPE    user_type;
};

class CustomerInfo{
  public:
    CustomerInfo(){
      this->l_id = 0;
      this->c_id = 0;
      this->last_name = {0};
      this->first_name = {0};
      this->phone_num = {0};
      this->e_mail_addr = {0};
    }
    int l_id;
    int c_id;
    std::string last_name;
    std::string first_name;
    std::string birthday;
    std::string  phone_num;
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
    bool fetch(std::string where, LoginInfo &login_info_from_db);
    bool update_pass(std::string login, std::string hashed_new_pass, std::string new_salt);
    bool update_login(std::string login, std::string new_login);
    bool update(std::string set, std::string where);
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
 *e_mail_addr*
 */
class CustomerInfoDao: public DataBase{
  public:
    CustomerInfoDao(std::string dbname, std::string user, std::string password);
    ~CustomerInfoDao(){};
    bool put(int l_id, std::string last_name, std::string first_name, std::string birthday, std::string phone_num, std::string e_mail_addr);
    bool fetch(std::string where, CustomerInfo &customer_info_from_db);
    bool update_name(int c_id, std::string last_name, std::string first_name){};
    bool update_e_mail(int c_id, std::string e_mail_addr){};
};

#endif
