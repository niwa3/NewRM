#include "relation_creater.h"

//========class relation_creater=========
std::vector<Relationship> RelationCreater::create_relationship_from_device(DeviceInfo device_info){
  ServiceManageFuncs smf("db.conf");
  //wanna fetch serviceinfos by data type, privacy level, and interval
  std::vector<ServiceInfo> matched_services = smf.fetch_Sinfo_for_matching(device_info.data_type, device_info.default_privacy_standard, device_info.interval);
  for(std::vector<ServiceInfo>::iterator ms_itr=matched_services.begin(); ms_itr!=matched_services.end(); ms_itr++){
    std::cout<<ms_itr->service_name<<std::endl;
  }
  std::vector<Relationship> r;
  return r;
}
