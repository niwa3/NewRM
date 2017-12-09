#ifndef __INCLUDED_TYPE_H__
#define __INCLUDED_TYPE_H__

#include <iostream>
#include <vector>
#include "./define.h"

//Customer is the user who has sensor or actuator
class Customer{
  private:
    Customer_id cid;
    Device_id did;
    Privacy_lvl plvl;
    Device_type ntype;
    Data_type dtype;
    Interval interval;
    Address address;

  public:
    int setCustomerid(Customer_id);
    int setDeviceid(Device_id);
    int setPrivacyLvl(Privacy_lvl);
    int setDeviceType(Device_type);
    int setDataType(Data_type);
    int setInterval(Interval);
    int setAddress(Address);
    Customer_id getCustomerid();
    Device_id getDeviceid();
    Privacy_lvl getPrivacyLvl(Privacy_lvl);
    Device_type getDviceType();
    Data_type getDataType();
    Interval getInterval();
    Address getAddress();
    Customer();
    ~Customer();
};


#endif
