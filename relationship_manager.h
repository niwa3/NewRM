#ifndef __INCLUDED_RM_FUNC_H__
#define __INCLUDED_RM_FUNC_H__

#include "manage.h"
#include "relation_creater.h"

/* リレーションシップマネージャ内の関数を定義するファイル
 * CustomerとVendorに分けてそれぞれの関数を定義する．
 */
namespace RelationshipManager{

class CustomerFunc{
  public:
    CustomerFunc(){};
    ~CustomerFunc(){};
    bool reg_new_device(int c_id, std::string device_name, int default_pricacy_standard, DEVICETYPE device_type, DATATYPE data_type, int interval, std::string location);
    bool show_device();
    bool del_device();
    bool show_relationship();
    bool mod_relationship();
    bool del_relationship();
};

class VendorFunc{
  public:
    VendorFunc(){};
    ~VendorFunc(){};
    bool reg_service();
    bool show_service();
    bool del_service();
    bool show_relationship();
    bool del_relationship();
};

}
#endif
