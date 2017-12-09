#ifndef __INCLUDED_RM_FUNC_H__
#define __INCLUDED_RM_FUNC_H__

#include "manage/manage.h"
//#include "relation_creater.h"

/* リレーションシップマネージャ内の関数を定義するファイル
 * CustomerとVenderに分けてそれぞれの関数を定義する．
 */
namespace RelationshipManager{

class CustomerFunc{
  public:
    CustomerFunc(){};
    ~CustomerFunc(){};
    //create_customer func returns customer id that is assigned automatically
    int create_customer(int l_id, std::string last_name, std::string first_name, std::string birthday, std::string phone_num, std::string e_mail_addr);
    bool reg_new_device(int c_id, std::string device_name, int default_pricacy_standard, DEVICETYPE device_type, DATATYPE data_type, int interval, std::string location);
    std::vector<DeviceInfo> show_device(int c_id);
    bool mod_device(DeviceInfo device);
    bool del_device(int d_id);
    std::vector<Relationship> show_relationship_by_d_id(int d_id);
    std::vector<Relationship> show_relationship_by_c_id(int c_id);
    bool mod_relationship(Relationship modified_relationshp);
    bool del_relationship();
};

class VenderFunc{
  public:
    VenderFunc(){};
    ~VenderFunc(){};
    int create_vendor(int l_id, std::string name, std::string phone_num, std::string e_mail_addr);
    bool reg_new_service(int v_id, std::string service_name, int required_privacy_standard, DATATYPE data_type, int interval);
    std::vector<ServiceInfo> show_service(int v_id);
    bool del_service(int s_id);
    std::vector<Relationship> show_relationship_by_s_id(int s_id);
    std::vector<Relationship> show_relationship_by_v_id(int v_id);
    bool del_relationship();
};

}
#endif
