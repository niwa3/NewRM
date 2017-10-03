#include "relation_creater.h"

int main(){
  RelationCreater r;
  ServiceManageFuncs smf("db.conf");
//  smf.register_Sinfo(1, "http://service1", 3, DATATYPE::POWER, 200);
  DeviceManageFuncs dmf("db.conf");
//  dmf.register_Dinfo(18, "http://device1", 1, DEVICETYPE::SENSOR, DATATYPE::POWER, 100, "http://gateway1");
  std::vector<DeviceInfo> d = dmf.fetch_Dinfo_by_c_id(18);
  std::cout<<d.begin()->device_name<<std::endl;
  r.create_relationship_from_device(*(d.begin()));
  return 0;
}
