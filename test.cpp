//#include "relation_creater.h"
#include "relationship_manager.h"

int main(){
  std::vector<DeviceInfo> vec_device;
  int i = 0;
  while(i<10){
    i++;
    DeviceInfo device;
    device.c_id = 19;
    device.device_name = "http://gateway19/sensor" + std::to_string(i);
    device.device_type = DEVICETYPE::SENSOR;
    device.data_type = DATATYPE::POWER;
    device.default_privacy_standard = 1;
    device.interval = 100;
    device.location = "http://gateway19";
    vec_device.push_back(device);
  }
  RelationshipManager::CustomerFunc cf;
  cf.reg_new_device(vec_device);
  return 0;
}
