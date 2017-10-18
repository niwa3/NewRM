#include "relation_creater.h"

//========class relation_creater=========
std::vector<Relationship> RelationCreater::create_relationship_from_device(DeviceInfo device_info){
  ServiceManageFuncs smf("db.conf");
  std::vector<ServiceInfo> matched_services = smf.fetch_Sinfo_for_matching(device_info.data_type, device_info.default_privacy_standard, device_info.interval);
  std::vector<Relationship> new_relationships;
  for(std::vector<ServiceInfo>::iterator ms_itr=matched_services.begin(); ms_itr!=matched_services.end(); ms_itr++){
    Relationship tmp_relationship = Relationship();
    tmp_relationship.d_id = device_info.d_id;
    tmp_relationship.device_name = device_info.device_name;
    tmp_relationship.s_id = ms_itr->s_id;
    tmp_relationship.service_name = ms_itr->service_name;
    tmp_relationship.anonymity_method = ANONYMITYMETHOD::FLAT;
    tmp_relationship.privacy_standard = device_info.default_privacy_standard;
    tmp_relationship.interval = ms_itr->interval;
    tmp_relationship.location = device_info.location;
    new_relationships.push_back(tmp_relationship);
  }
  return new_relationships;
}

std::vector<Relationship> RelationCreater::create_relationship_from_service(ServiceInfo service_info){
  DeviceManageFuncs dmf("db.conf");
  std::vector<DeviceInfo> matched_devices = dmf.fetch_Dinfo_for_matching(service_info.data_type, service_info.required_privacy_standard, service_info.interval);
  std::vector<Relationship> new_relationships;
  for(std::vector<DeviceInfo>::iterator md_itr=matched_devices.begin(); md_itr!=matched_devices.end(); md_itr++){
    Relationship tmp_relationship = Relationship();
    tmp_relationship.d_id = md_itr->d_id;
    tmp_relationship.device_name = md_itr->device_name;
    tmp_relationship.s_id = service_info.s_id;
    tmp_relationship.service_name = service_info.service_name;
    tmp_relationship.anonymity_method = ANONYMITYMETHOD::FLAT;
    tmp_relationship.privacy_standard = md_itr->default_privacy_standard;
    tmp_relationship.interval = service_info.interval;
    tmp_relationship.location = md_itr->location;
    new_relationships.push_back(tmp_relationship);
  }
  return new_relationships;
}
