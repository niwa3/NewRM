#include "relationship_manager.h"

//============class CustomerFunc============
int RelationshipManager::CustomerFunc::create_customer(
    int l_id, std::string last_name,
    std::string first_name,
    std::string birthday,
    std::string phone_num,
    std::string e_mail_addr)
{
  CustomerManageFuncs cmf("cmdb.conf");
  return cmf.register_Cinfo(l_id, last_name, first_name, birthday, phone_num, e_mail_addr);
}


bool RelationshipManager::CustomerFunc::reg_new_device(
    int c_id,
    std::string device_name,
    int default_pricacy_standard,
    DEVICETYPE device_type,
    DATATYPE data_type,
    int interval, std::string location)
{
  DeviceManageFuncs dmf("cmdb.conf");
  int d_id = 
    dmf.register_Dinfo(
      c_id, device_name,
      default_pricacy_standard,
      device_type, data_type,
      interval,
      location
    );
  if(d_id != -1)
  {
    RelationshipManageFuncs rmf("db.conf");
    RelationCreater rc;
    if(!rmf.register_Relation(
        rc.create_relationship_from_device(
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
  DeviceManageFuncs dmf("cmdb.conf");
  std::vector<DeviceInfo> devices = dmf.fetch_Dinfo_by_c_id(c_id);
  return devices;
}


bool RelationshipManager::CustomerFunc::del_device(int d_id){
  DeviceManageFuncs dmf("cmdb.conf");
  RelationshipManageFuncs rmf("cmdb.conf");
  if(rmf.delete_Relation_by_d_id(d_id))
    return dmf.delete_Dinfo_by_d_id(d_id);
  else
    return false;
}


std::vector<Relationship> RelationshipManager::CustomerFunc::show_relationship_by_d_id(int d_id){
  RelationshipManageFuncs rmf("cmdb.conf");
  std::vector<Relationship> relationships = rmf.fetch_Relation_by_d_id(d_id);
  return relationships;
}


std::vector<Relationship> RelationshipManager::CustomerFunc::show_relationship_by_c_id(int c_id){
  RelationshipManageFuncs rmf("cmdb.conf");
  std::vector<Relationship> relationships = rmf.fetch_Relation_by_c_id(c_id);
  return relationships;
}
//===========================================


//============class VenderFunc===============
int RelationshipManager::VenderFunc::create_vendor(int l_id, std::string name, std::string phone_num, std::string e_mail_addr){
  VenderManageFuncs vmf("cmdb.conf");
  return vmf.register_Vinfo(l_id, name, phone_num, e_mail_addr);
}


bool RelationshipManager::VenderFunc::reg_new_service(
    int v_id,
    std::string service_name,
    int required_privacy_standard,
    DATATYPE data_type,
    int interval)
{

  ServiceManageFuncs ser_m("cmdb.conf");
  int s_id = ser_m.register_Sinfo(v_id, service_name, required_privacy_standard, data_type, interval);

  if(s_id != -1){
    RelationshipManageFuncs rmf("db.conf");
    RelationCreater rc;
    if(!rmf.register_Relation(rc.create_relationship_from_service(ser_m.fetch_Sinfo_by_s_id(s_id))).empty()){
      return true;
    }
    else return false;
  }
  else return false;

};


std::vector<ServiceInfo> RelationshipManager::VenderFunc::show_service(int v_id){
  ServiceManageFuncs smf("cmdb.conf");
  std::vector<ServiceInfo> services = smf.fetch_Sinfo_by_v_id(v_id);
  return services;
}


bool RelationshipManager::VenderFunc::del_service(int s_id){
  ServiceManageFuncs smf("cmdb.conf");
  RelationshipManageFuncs rmf("cmdb.conf");

  if(rmf.delete_Relation_by_s_id(s_id))
    return smf.delete_Sinfo_by_s_id(s_id);
  else
    return false;
}


std::vector<Relationship> RelationshipManager::VenderFunc::show_relationship_by_s_id(int s_id){
  RelationshipManageFuncs rmf("cmdb.conf");
  std::vector<Relationship> relationships = rmf.fetch_Relation_by_s_id(s_id);
  return relationships;
}


std::vector<Relationship> RelationshipManager::VenderFunc::show_relationship_by_v_id(int v_id){
  RelationshipManageFuncs rmf("cmdb.conf");
  std::vector<Relationship> relationships = rmf.fetch_Relation_by_v_id(v_id);
  return relationships;
}
//===========================================
