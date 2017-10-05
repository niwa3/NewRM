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

enum class USERTYPE { NONE, CUSTOMER, VENDER };
enum class DEVICETYPE { NONE, SENSOR, ACTUATOR };
enum class DATATYPE { NONE, POWER, CO2, TEMP };
enum class ANONYMITYMETHOD { NONE, NOISE, FLAT };

//login情報データモデル
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
    USERTYPE user_type;
};

//Customer情報データモデル
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
    std::string phone_num;
    std::string e_mail_addr;
};

//Device情報データモデル
class DeviceInfo{
  public:
    DeviceInfo(){
      this->c_id = 0;
      this->d_id = 0;
      this->device_name = {0};
      this->default_privacy_standard = 0;
      this->device_type = DEVICETYPE::NONE;
      this->data_type = DATATYPE::NONE;
      this->interval = 0;
      this->location = {0};
    }
    int c_id;
    int d_id;
    std::string device_name;
    int default_privacy_standard;
    DEVICETYPE device_type;
    DATATYPE data_type;
    int interval;
    std::string location;
};

//Vender情報データモデル
class VenderInfo{
  public:
    VenderInfo(){
      this->l_id = 0;
      this->v_id = 0;
      this->name = {0};
      this->phone_num = {0};
      this->e_mail_addr = {0};
    }
    int l_id;
    int v_id;
    std::string name;
    std::string phone_num;
    std::string e_mail_addr;
};

//Service情報用データモデル
class ServiceInfo{
  public:
    ServiceInfo(){
      this->v_id = 0;
      this->s_id = 0;
      this->service_name = {0};
      this->required_privacy_standard = 0;
      this->data_type = DATATYPE::NONE;
      this->interval = 0;
    }
    int v_id;
    int s_id;
    std::string service_name;
    int required_privacy_standard;
    DATATYPE data_type;
    int interval;
};

class Relationship{
  public:
    Relationship(){
      this->r_id = 0;
      this->d_id = 0;
      this->device_name = {0};
      this->s_id = 0;
      this->service_name = {0};
      this->anonymity_method = ANONYMITYMETHOD::NONE;
      this->privacy_standard = 0;
      this->interval = 0;
      this->location = {0};
    }
    ~Relationship(){};
    int r_id;
    int d_id;
    std::string device_name;
    int s_id;
    std::string service_name;
    ANONYMITYMETHOD anonymity_method;
    int privacy_standard;
    int interval;
    std::string location;
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
 * ログイン用の情報にアクセス
 * 属性：
 * int id
 * std::string login
 * std::string hashed_pass
 * std::string slat
 * USERTYPE user_type
 */
class LoginInfoDao: public DataBase{
  public:
    LoginInfoDao(std::string dbname, std::string user, std::string password);
    ~LoginInfoDao(){};
    bool put(std::string login, std::string hashed_pass, std::string salt, USERTYPE user_type );
    bool fetch(std::string where, LoginInfo &login_info_from_db);
    bool update(std::string set_attr, std::string where);
};

/*
 * コンシューマの情報にアクセス
 * 属性：
 * int l_id
 * int id
 * std::string last_name
 * std::string first_name
 * std::string birthday
 * std::string phone_num
 * std::string e_mail_addr
 */
class CustomerInfoDao: public DataBase{
  public:
    CustomerInfoDao(std::string dbname, std::string user, std::string password);
    ~CustomerInfoDao(){};
    bool put(int l_id, std::string last_name, std::string first_name, std::string birthday, std::string phone_num, std::string e_mail_addr);
    bool fetch(std::string where, CustomerInfo &customer_info_from_db);
    bool fetch(std::string where, std::vector<CustomerInfo> &customers_info_from_db);
    bool update(std::string set_attr, std::string where);
};

/*
 * コンシューマの所有するデバイスに関する情報にアクセス
 * 属性：
 * int c_id
 * int id
 * std::string device_name;
 * int default_privacy_standard
 * DEVICETYPE device_type
 * DATATYPE data_type
 * int interval
 * std::string location
 */
class DeviceInfoDao: public DataBase{
  public:
    DeviceInfoDao(std::string dbname, std::string user, std::string password);
    ~DeviceInfoDao(){};
    bool put(int c_id, std::string device_name, int default_privacy_standard, DEVICETYPE device_type, DATATYPE data_type, int interval, std::string location);
    bool fetch(std::string where, DeviceInfo &device_info_from_db);
    bool fetch(std::string where, std::vector<DeviceInfo> &devices_info_from_db);
    bool update(std::string set_attr, std::string where);
};

/*
 * venderの情報にアクセス
 * 属性：
 * int l_id
 * int id
 * std::string name
 * std::string phone_num
 * std::string e_mail_addr
 */
class VenderInfoDao: public DataBase{
  public:
    VenderInfoDao(std::string dbname, std::string user, std::string password);
    ~VenderInfoDao(){};
    bool put(int l_id, std::string name, std::string phone_num, std::string e_mail_addr);
    bool fetch(std::string where, VenderInfo &vender_info_from_db);
    bool fetch(std::string where, std::vector<VenderInfo> &venders_info_from_db);
    bool update(std::string set_attr, std::string where);
};

/*
 * venderの提供するサービスに関する情報にアクセス
 * int v_id;
 * int id;
 * std::string service_name;
 * int required_privacy_standard;
 * DATATYPE data_type;
 * int interval;
 */
class ServiceInfoDao: public DataBase{
  public:
    ServiceInfoDao(std::string dbname, std::string user, std::string password);
    ~ServiceInfoDao(){};
    bool put(int v_id, std::string service_name, int required_privacy_standard, DATATYPE data_type, int interval);
    bool fetch(std::string where, ServiceInfo &service_info_from_db);
    bool fetch(std::string where, std::vector<ServiceInfo> &services_info_from_db);
    bool update(std::string set_attr, std::string where);
};

/*
 * relationshipデータベースにアクセス
 * int r_id;
 * int d_id;
 * int s_id;
 * ANONYMITYMETHOD anonymity_method;
 * int privacy_standard;
 * int interval;
 * std::string location;
 */
class RelationshipDao: public DataBase{
  public:
    RelationshipDao(std::string dbname, std::string user, std::string password);
    ~RelationshipDao(){};
    bool put(int d_id, std::string device_name, int s_id, std::string service_name, ANONYMITYMETHOD anonymity_method, int privacy_standard, int interval, std::string location);
    bool put_all(std::vector<Relationship> relationship);
    bool fetch(std::string where, Relationship &relationship_from_db);
    bool fetch(std::string where, std::vector<Relationship> &relationships_from_db);
    bool update(std::string set_attr, std::string where);
};
#endif
