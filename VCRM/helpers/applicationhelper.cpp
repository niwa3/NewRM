#include "applicationhelper.h"


QList<QVariantMap> ApplicationHelper::createRelationMap(
    ServiceInfo service,
    QList<DeviceInfo> deviceList
)
{
  QList<QVariantMap> relationshipList;
  for (DeviceInfo device : deviceList) {
    QVariantMap relation;
    relation.insert("dId", device.id());
    relation.insert("deviceName", device.deviceName());
    relation.insert("sId", service.id());
    relation.insert("serviceName", service.serviceName());
    relation.insert("anonymityMethod", ANONYMITYMETHOD::NOISE);
    relation.insert("privacyStandard", device.defaultPrivacyStandard());
    relation.insert("interval", service.interval());
    relation.insert("location", device.location());
    relationshipList.append(relation);
  }

  return relationshipList;
}
