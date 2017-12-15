//#include "relation_creater.h"
#include "relationship_manager.h"

int main(){
  std::vector<Relationship> relationships;
  RelationshipManager::CustomerFunc cf;
  relationships = cf.show_relationship_by_c_id(18);
  cf.del_relationship(relationships);
  return 0;
}
