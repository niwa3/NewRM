#include "rm_func.h"

bool RelationshipManager::CustomerFunc::reg_new_device(
    int c_id, std::string device_name,
    int default_pricacy_standard,
    DEVICETYPE device_type,
    DATATYPE data_type,
    int interval, std::string location)
{

  DeviceManageFuncs dev_m("cmdb.conf");
  if(dev_m.register_Dinfo(c_id, device_name, default_pricacy_standard, device_type, data_type, interval, location)){

  }

}
