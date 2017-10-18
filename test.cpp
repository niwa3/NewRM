#include "relation_creater.h"
#include "relationship_manager.h"

int main(){
  RelationshipManager::CustomerFunc cf;
  std::cout<<cf.del_device(8)<<std::endl;

  return 0;
}
