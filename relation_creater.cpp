#include "relation_creater.h"

//========class relation_creater=========
std::vector<Relationship> RelationCreater::create_relationship_from_device(DeviceInfo device_info){
  ServiceManageFuncs smf("db.conf");
  std::vector<ServiceInfo> matched_services = smf.fetch_Sinfo_for_matching(device_info.data_type, device_info.default_privacy_standard, device_info.interval);
  std::vector<Relationship> new_relationships;
  for(std::vector<ServiceInfo>::iterator ms_itr=matched_services.begin(); ms_itr!=matched_services.end(); ms_itr++){
    Relationship tmp_relationship = Relationship();
    tmp_relationship.d_id = device_info.d_id;
    tmp_relationship.s_id = ms_itr->s_id;
    tmp_relationship.anonymity_method = ANONYMITYMETHOD::FLAT;
    tmp_relationship.privacy_standard = device_info.default_privacy_standard;
    tmp_relationship.interval = ms_itr->interval;
    tmp_relationship.location = device_info.location;
    new_relationships.push_back(tmp_relationship);
  }
  return new_relationships;
}
