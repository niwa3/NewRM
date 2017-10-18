#include "relationship_manager.h"

//============class CustomerFunc============
bool RelationshipManager::CustomerFunc::reg_new_device(
    int c_id,
    std::string device_name,
    int default_pricacy_standard,
    DEVICETYPE device_type,
    DATATYPE data_type,
    int interval, std::string location)
{

  DeviceManageFuncs dmf("cmdb.conf");
  if(dmf.register_Dinfo(c_id, device_name, default_pricacy_standard, device_type, data_type, interval, location)){
    RelationshipManageFuncs rmf("db.conf");
    RelationCreater rc;
    if(rmf.register_Relation(rc.create_relationship_from_device(dmf.fetch_Dinfo_by_device_name(device_name)))){
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


//先にリレーションシップを消さないと外部参照制約によってエラー吐く
bool RelationshipManager::CustomerFunc::del_device(int d_id){
  DeviceManageFuncs dmf("cmdb.conf");
  RelationshipManageFuncs rmf("cmdb.conf");

  return dmf.delete_Dinfo_by_d_id(d_id);
}
//===========================================


//============class VendorFunc===============
bool RelationshipManager::VendorFunc::reg_new_service(
    int v_id,
    std::string service_name,
    int required_privacy_standard,
    DATATYPE data_type,
    int interval)
{

  ServiceManageFuncs ser_m("cmdb.conf");
  if(ser_m.register_Sinfo(v_id, service_name, required_privacy_standard, data_type, interval)){
    RelationshipManageFuncs rmf("db.conf");
    RelationCreater rc;
    if(rmf.register_Relation(rc.create_relationship_from_service(ser_m.fetch_Sinfo_by_service_name(service_name)))){
      return true;
    }
    else return false;
  }
  else return false;

};


std::vector<ServiceInfo> RelationshipManager::VendorFunc::show_service(int v_id){
  ServiceManageFuncs smf("cmdb.conf");
  std::vector<ServiceInfo> services = smf.fetch_Sinfo_by_v_id(v_id);
  return services;
}

//===========================================
