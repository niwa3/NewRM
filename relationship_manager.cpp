#include "relationship_manager.h"

#define DB_CONF "./conf/db.conf"
#define CMDB_CONF "./conf/cmdb.conf"

//============RelationCreater===============
namespace RelationCreater{

std::vector<Relationship> create_relationship_from_device(DeviceInfo device_info){
  ServiceManageFuncs smf(DB_CONF);
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


std::vector<Relationship> create_relationship_from_service(ServiceInfo service_info){
  DeviceManageFuncs dmf(DB_CONF);
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

}
//==========================================

//============class CustomerFunc============
int RelationshipManager::CustomerFunc::create_customer(
    int l_id, std::string last_name,
    std::string first_name,
    std::string birthday,
    std::string phone_num,
    std::string e_mail_addr)
{
  CustomerManageFuncs cmf(CMDB_CONF);
  return cmf.register_Cinfo(l_id, last_name, first_name, birthday, phone_num, e_mail_addr);
}


bool RelationshipManager::CustomerFunc::reg_new_device(
    int c_id,
    std::string device_name,
    int default_privacy_standard,
    DEVICETYPE device_type,
    DATATYPE data_type,
    int interval, std::string location)
{
  DeviceManageFuncs dmf(CMDB_CONF);
  int d_id =
    dmf.register_Dinfo(
      c_id, device_name,
      default_privacy_standard,
      device_type, data_type,
      interval,
      location
    );
  if(d_id != -1)
  {
    RelationshipManageFuncs rmf(DB_CONF);
    if(!rmf.register_Relation(
        RelationCreater::create_relationship_from_device(
          dmf.fetch_Dinfo_by_d_id(d_id)
          )
        ).empty()
      )
    {
      return true;
    }
    else return false;
  }
  else return false;
}


std::vector<DeviceInfo> RelationshipManager::CustomerFunc::show_device(int c_id){
  DeviceManageFuncs dmf(CMDB_CONF);
  std::vector<DeviceInfo> devices = dmf.fetch_Dinfo_by_c_id(c_id);
  return devices;
}


bool RelationshipManager::CustomerFunc::mod_device(DeviceInfo device){
  DeviceManageFuncs dmf(CMDB_CONF);
  return true;
}


bool RelationshipManager::CustomerFunc::del_device(int d_id){
  DeviceManageFuncs dmf(CMDB_CONF);
  RelationshipManageFuncs rmf(CMDB_CONF);
  if(rmf.delete_Relation_by_d_id(d_id))
    return dmf.delete_Dinfo_by_d_id(d_id);
  else
    return false;
}


std::vector<Relationship> RelationshipManager::CustomerFunc::show_relationship_by_d_id(int d_id){
  RelationshipManageFuncs rmf(CMDB_CONF);
  std::vector<Relationship> relationships = rmf.fetch_Relation_by_d_id(d_id);
  return relationships;
}


std::vector<Relationship> RelationshipManager::CustomerFunc::show_relationship_by_c_id(int c_id){
  RelationshipManageFuncs rmf(CMDB_CONF);
  std::vector<Relationship> relationships = rmf.fetch_Relation_by_c_id(c_id);
  return relationships;
}


bool RelationshipManager::CustomerFunc::mod_relationship(Relationship modified_relationshp){
  RelationshipManageFuncs rmf(CMDB_CONF);
  std::string SET_ATTR =
    "anonymity_method="+std::to_string((int)modified_relationshp.anonymity_method)+
    ",privacy_standard="+std::to_string(modified_relationshp.privacy_standard)+
    ",interval="+std::to_string(modified_relationshp.interval)+
    ",location='"+modified_relationshp.location+"'";
  return
    rmf.update_Relation_by_r_id(
      modified_relationshp.r_id,
      SET_ATTR
    );
}
//===========================================


//============class VenderFunc===============
int RelationshipManager::VenderFunc::create_vendor(
    int l_id, std::string name,
    std::string phone_num,
    std::string e_mail_addr)
{
  VenderManageFuncs vmf(CMDB_CONF);
  return vmf.register_Vinfo(l_id, name, phone_num, e_mail_addr);
}


bool RelationshipManager::VenderFunc::reg_new_service(
    int v_id,
    std::string service_name,
    int required_privacy_standard,
    DATATYPE data_type,
    int interval)
{
  ServiceManageFuncs ser_m(CMDB_CONF);
  int s_id = ser_m.register_Sinfo(v_id, service_name, required_privacy_standard, data_type, interval);

  if(s_id != -1){
    RelationshipManageFuncs rmf(DB_CONF);
    if(!rmf.register_Relation(
          RelationCreater::create_relationship_from_service(
            ser_m.fetch_Sinfo_by_s_id(s_id)
          )
        ).empty()){
      return true;
    }
    else return false;
  }
  else return false;
};


std::vector<ServiceInfo> RelationshipManager::VenderFunc::show_service(int v_id){
  ServiceManageFuncs smf(CMDB_CONF);
  std::vector<ServiceInfo> services = smf.fetch_Sinfo_by_v_id(v_id);
  return services;
}


bool RelationshipManager::VenderFunc::del_service(int s_id){
  ServiceManageFuncs smf(CMDB_CONF);
  RelationshipManageFuncs rmf(CMDB_CONF);

  if(rmf.delete_Relation_by_s_id(s_id))
    return smf.delete_Sinfo_by_s_id(s_id);
  else
    return false;
}


std::vector<Relationship> RelationshipManager::VenderFunc::show_relationship_by_s_id(int s_id){
  RelationshipManageFuncs rmf(CMDB_CONF);
  std::vector<Relationship> relationships = rmf.fetch_Relation_by_s_id(s_id);
  return relationships;
}


std::vector<Relationship> RelationshipManager::VenderFunc::show_relationship_by_v_id(int v_id){
  RelationshipManageFuncs rmf(CMDB_CONF);
  std::vector<Relationship> relationships = rmf.fetch_Relation_by_v_id(v_id);
  return relationships;
}
//===========================================
