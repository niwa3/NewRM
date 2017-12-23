//#include "relation_creater.h"
#include "relationship_manager.h"

int main(){
  std::vector<ServiceInfo> vec_service;
  int i = 0;
  while(i<10){
    i++;
    ServiceInfo service;
    service.v_id = 1;
    service.service_name = "http://vendor1/service" + std::to_string(i);
    service.data_type = DATATYPE::POWER;
    service.required_privacy_standard = 3;
    service.interval = 100;
    vec_service.push_back(service);
  }
  RelationshipManager::VenderFunc vf;
  vf.reg_new_service(vec_service);
  return 0;
}
