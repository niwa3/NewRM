#include "relation_creater.h"
#include "relationship_manager.h"

int main(){
  LoginManageFuncs lmf("cmdb.conf");
  int l_id = lmf.register_Linfo("megu", "megudesu", USERTYPE::CUSTOMER);
  std::vector<Relationship> relationships;
  RelationshipManager::CustomerFunc cf;
  std::cout<<"new l_id: "<<l_id<<std::endl;
  int c_id;
  c_id = cf.create_customer(l_id, "meguwin", "motonobu", "1992-09-09", "90928108270", "jskdj@example.com");
  std::cout<<"new c_id: "<<c_id<<std::endl;
  int d_id;
  d_id = cf.reg_new_device(c_id, "http://senser6", 1, DEVICETYPE::SENSOR, DATATYPE::POWER, 100, "http://gateway2");
  std::cout<<"new d_id: "<<d_id<<std::endl;
  relationships = cf.show_relationship_by_c_id(c_id);
  //std::cout<<cf.del_device(10)<<std::endl;
  //cf.reg_new_device(18, "http://senser2", 1, DEVICETYPE::SENSOR, DATATYPE::POWER, 100, "http://gateway1");
  //RelationshipManager::VendorFunc vf;
  //vf.del_service(1);
  //relationships = vf.show_relationship_by_v_id(1);

  for(std::vector<Relationship>::iterator r_itr=relationships.begin(); r_itr!=relationships.end(); r_itr++){
    std::cout<<r_itr->r_id<<", "<<r_itr->service_name<<", "<<r_itr->device_name<<std::endl;
  }

  return 0;
}
