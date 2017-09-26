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
    LoginInfo fetch_Linfo_by_login(std::string login);
    LoginInfo fetch_Linfo_by_l_id(int l_id);
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

#endif
