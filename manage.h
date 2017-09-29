#ifndef __INCLUDED_MANAGE_H__
#define __INCLUDED_MANAGE_H__

#include "dao.h"
#include <fstream>
#include <memory>

class LoginManager{
  public:
    LoginManager(std::string filename);
    ~LoginManager(){};
    bool register_Linfo(std::string login, std::string password, USERTYPE user_type);
    //fetchの条件は必要になったら随時追加する
    //ここでは，とりあえず，外部キーになっているidから検索できる関数を用意する．
    LoginInfo fetch_Linfo_by_login(std::string login);
    LoginInfo fetch_Linfo_by_l_id(int l_id);
    //各種infoの変更は対称のIDからで指定して変更すること
    bool update_Linfo_by_l_id(int l_id, std::string set_attr);
  private:
    std::unique_ptr<LoginInfoDao> l_dao;
};

class CustomerManager{
  public:
    CustomerManager(std::string filename);
    ~CustomerManager(){};
    bool register_Cinfo(int l_id, std::string last_name, std::string first_name, std::string birthday, std::string phone_num, std::string e_mail_addr);
    CustomerInfo fetch_Cinfo_by_l_id(int l_id);
    bool update_Cinfo_by_c_id(int c_id, std::string set_attr);
  private:
    std::unique_ptr<CustomerInfoDao> c_dao;
};

class DeviceManager{
  public:
    DeviceManager(std::string filename);
    ~DeviceManager(){};
    bool register_Dinfo(int c_id, std::string device_name, int default_privacy_standard, DEVICETYPE device_type, DATATYPE data_type, int interval, std::string location);
    DeviceInfo fetch_Dinfo_by_c_id(int c_id);
    bool update_Dinfo_by_d_id(int d_id, std::string set_attr);
  private:
    std::unique_ptr<DeviceInfoDao> d_dao;
};

class VenderManager{
  public:
    VenderManager(std::string filename);
    ~VenderManager(){};
    bool register_Vinfo(int l_id, std::string name, std::string phone_num, std::string e_mail_addr);
    VenderInfo fetch_Vinfo_by_l_id(int l_id);
    bool update_Vinfo_by_v_id(int v_id, std::string set_attr);
  private:
    std::unique_ptr<VenderInfoDao> v_dao;
};

class ServiceManager{
  public:
    ServiceManager(std::string filename);
    ~ServiceManager(){};
    bool register_Sinfo(int v_id, std::string service_name, int required_privacy_standard, DATATYPE data_type, int interval);
    ServiceInfo fetch_Sinfo_by_v_id(int v_id);
    bool update_Sinfo_by_s_id(int s_id, std::string set_attr);

  private:
    std::unique_ptr<ServiceInfoDao> s_dao;
};

class RelationshipManager{
  public:
    RelationshipManager(std::string filename);
    ~RelationshipManager(){};
    bool register_Relation(int v_id, std::string service_name, int required_privacy_standard, DATATYPE data_type, int interval);
    Relationship fetch_Relation_by_d_id(int d_id);
    Relationship fetch_Relation_by_s_id(int s_id);
    bool update_Relation_by_r_id(int r_id, std::string set_attr);

  private:
    std::unique_ptr<ServiceInfoDao> s_dao;
};

#endif
