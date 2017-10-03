#ifndef __INCLUDED_RELATION_CREATER_H__
#define __INCLUDED_RELATION_CREATER_H__

#include "manage.h"
#include <vector>

class RelationCreater{
  public:
    std::vector<Relationship> create_relationship_from_device(DeviceInfo device_info);
    std::vector<Relationship> create_relationship_from_service(ServiceInfo service_info);
};

#endif
