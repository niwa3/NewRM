#ifndef __INCLUDED_PPM_FUNC_H__
#define __INCLUDED_PPM_FUNC_H__
/* プライバシマネージャ内の関数を定義するファイル
 * CustomerとVendorに分けてそれぞれの関数を定義する．
 */
namespace PrivacyPolicyManager{

class CustomerFunc{
  public:
    CustomerFunc(){};
    ~CustomerFunc(){};
    bool reg_device();
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
