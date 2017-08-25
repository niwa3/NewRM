#ifndef __INCLUDED_MANAGE_H__
#define __INCLUDED_MANAGE_H__

#include "dao.h"
#include <fstream>
#include <memory>

class Manager{
  public:
    Manager(std::string filename);
    ~Manager(){};
    bool register_Linfo(std::string login, std::string password, USERTYPE user_type);
    bool register_Cinfo(int l_id, std::string last_name, std::string first_name, std::string birthday, std::string phone_num, std::string e_mail_addr);
    LoginInfo fetch_Linfo_by_login(std::string login);
    LoginInfo fetch_Linfo_by_l_id(int l_id);
    CustomerInfo fetch_Cinfo_by_l_id(int l_id);
  private:
    std::unique_ptr<LoginInfoDao> l_dao;
    std::unique_ptr<CustomerInfoDao> c_dao;
};


#endif
