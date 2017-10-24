#ifndef __INCLUDED_MANAGE_H__
#define __INCLUDED_MANAGE_H__

#include "dao.h"
#include <fstream>
#include <memory>

class LoginManageFuncs{
  public:
    LoginManageFuncs(std::string filename);
    ~LoginManageFuncs(){};
    int register_Linfo(std::string login, std::string password, USERTYPE user_type);
    //fetchの条件は必要になったら随時追加する
    //ここでは，とりあえず，外部キーになっているidから検索できる関数を用意する．
    LoginInfo fetch_Linfo_by_login(std::string login);
    LoginInfo fetch_Linfo_by_l_id(int l_id);
    //各種infoの変更は対称のIDからで指定して変更すること
    bool update_Linfo_by_l_id(int l_id, std::string set_attr);
    bool delete_Linfo_by_l_id(int l_id);
  private:
    std::unique_ptr<LoginInfoDao> l_dao;
};

class CustomerManageFuncs{
  public:
    CustomerManageFuncs(std::string filename);
    ~CustomerManageFuncs(){};
    int register_Cinfo(int l_id, std::string last_name, std::string first_name, std::string birthday, std::string phone_num, std::string e_mail_addr);
    std::vector<CustomerInfo> fetch_Cinfo_by_l_id(int l_id);
    bool update_Cinfo_by_c_id(int c_id, std::string set_attr);
    bool delete_Cinfo_by_c_id(int c_id);
  private:
    std::unique_ptr<CustomerInfoDao> c_dao;
};

class DeviceManageFuncs{
  public:
    DeviceManageFuncs(std::string filename);
    ~DeviceManageFuncs(){};
    int register_Dinfo(int c_id, std::string device_name, int default_privacy_standard, DEVICETYPE device_type, DATATYPE data_type, int interval, std::string location);
    std::vector<DeviceInfo> fetch_Dinfo_by_c_id(int c_id);
    DeviceInfo fetch_Dinfo_by_d_id(int d_id);
    DeviceInfo fetch_Dinfo_by_device_name(std::string device_name);
    std::vector<DeviceInfo> fetch_Dinfo_for_matching(DATATYPE data_type, int privacy_standard, int interval);
    bool update_Dinfo_by_d_id(int d_id, std::string set_attr);
    bool delete_Dinfo_by_d_id(int d_id);
  private:
    std::unique_ptr<DeviceInfoDao> d_dao;
};

class VenderManageFuncs{
  public:
    VenderManageFuncs(std::string filename);
    ~VenderManageFuncs(){};
    int register_Vinfo(int l_id, std::string name, std::string phone_num, std::string e_mail_addr);
    std::vector<VenderInfo> fetch_Vinfo_by_l_id(int l_id);
    bool update_Vinfo_by_v_id(int v_id, std::string set_attr);
    bool delete_Vinfo_by_v_id(int v_id);
  private:
    std::unique_ptr<VenderInfoDao> v_dao;
};

class ServiceManageFuncs{
  public:
    ServiceManageFuncs(std::string filename);
    ~ServiceManageFuncs(){};
    int register_Sinfo(int v_id, std::string service_name, int required_privacy_standard, DATATYPE data_type, int interval);
    std::vector<ServiceInfo> fetch_Sinfo_by_v_id(int v_id);
    ServiceInfo fetch_Sinfo_by_s_id(int v_id);
    ServiceInfo fetch_Sinfo_by_service_name(std::string service_name);
    std::vector<ServiceInfo> fetch_Sinfo_for_matching(DATATYPE data_type, int privacy_standard, int interval);
    bool update_Sinfo_by_s_id(int s_id, std::string set_attr);
    bool delete_Sinfo_by_s_id(int s_id);
  private:
    std::unique_ptr<ServiceInfoDao> s_dao;
};

class RelationshipManageFuncs{
  public:
    RelationshipManageFuncs(std::string filename);
    ~RelationshipManageFuncs(){};
    int register_Relation(int d_id, std::string device_name, int s_id, std::string service_name, ANONYMITYMETHOD anonymity_method, int privacy_standard, int interval, std::string location);
    std::vector<int> register_Relation(std::vector<Relationship> new_relationships);
    std::vector<Relationship> fetch_Relation_by_d_id(int d_id);
    std::vector<Relationship> fetch_Relation_by_s_id(int s_id);
    std::vector<Relationship> fetch_Relation_by_c_id(int c_id);
    std::vector<Relationship> fetch_Relation_by_v_id(int v_id);
    bool update_Relation_by_r_id(int r_id, std::string set_attr);
    bool delete_Relation_by_r_id(int r_id);
    bool delete_Relation_by_d_id(int d_id);
    bool delete_Relation_by_s_id(int s_id);
  private:
    std::unique_ptr<RelationshipDao> r_dao;
};

#endif
