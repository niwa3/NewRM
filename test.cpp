#include "relation_creater.h"
#include "relationship_manager.h"

int main(){
  //RelationshipManager::CustomerFunc cf;
  std::vector<Relationship> relationships;
  //relationships = cf.show_relationship_by_d_id(15);
  //std::cout<<cf.del_device(10)<<std::endl;
  //cf.reg_new_device(18, "http://senser2", 1, DEVICETYPE::SENSOR, DATATYPE::POWER, 100, "http://gateway1");
  RelationshipManager::VendorFunc vf;
  //vf.del_service(1);
  relationships = vf.show_relationship_by_s_id(2);

  for(std::vector<Relationship>::iterator r_itr=relationships.begin(); r_itr!=relationships.end(); r_itr++){
    std::cout<<r_itr->r_id<<", "<<r_itr->service_name<<", "<<r_itr->device_name<<std::endl;
  }

  return 0;
}
