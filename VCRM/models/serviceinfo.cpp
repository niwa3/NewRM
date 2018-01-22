#include <treefrog/TreeFrogModel>
#include "serviceinfo.h"
#include "serviceinfoobject.h"

ServiceInfo::ServiceInfo()
  : TAbstractModel(), d(new ServiceInfoObject())
{
  d->id = 0;
  d->v_id = 0;
  d->required_privacy_standard = 0;
  d->data_type = 0;
  d->interval = 0;
}

ServiceInfo::ServiceInfo(const ServiceInfo &other)
  : TAbstractModel(), d(new ServiceInfoObject(*other.d))
{ }

ServiceInfo::ServiceInfo(const ServiceInfoObject &object)
  : TAbstractModel(), d(new ServiceInfoObject(object))
{ }

ServiceInfo::~ServiceInfo()
{
  // If the reference count becomes 0,
  // the shared data object 'ServiceInfoObject' is deleted.
}

int ServiceInfo::id() const
{
  return d->id;
}

QDateTime ServiceInfo::createdAt() const
{
  return d->created_at;
}

QDateTime ServiceInfo::updatedAt() const
{
  return d->updated_at;
}

int ServiceInfo::vId() const
{
  return d->v_id;
}

void ServiceInfo::setVId(int vId)
{
  d->v_id = vId;
}

QString ServiceInfo::serviceName() const
{
  return d->service_name;
}

void ServiceInfo::setServiceName(const QString &serviceName)
{
  d->service_name = serviceName;
}

int ServiceInfo::requiredPrivacyStandard() const
{
  return d->required_privacy_standard;
}

void ServiceInfo::setRequiredPrivacyStandard(int requiredPrivacyStandard)
{
  d->required_privacy_standard = requiredPrivacyStandard;
}

int ServiceInfo::dataType() const
{
  return d->data_type;
}

void ServiceInfo::setDataType(int dataType)
{
  d->data_type = dataType;
}

int ServiceInfo::interval() const
{
  return d->interval;
}

void ServiceInfo::setInterval(int interval)
{
  d->interval = interval;
}

ServiceInfo &ServiceInfo::operator=(const ServiceInfo &other)
{
  d = other.d;  // increments the reference count of the data
  return *this;
}

ServiceInfo ServiceInfo::create(int vId, const QString &serviceName, int requiredPrivacyStandard, int dataType, int interval)
{
  ServiceInfoObject obj;
  obj.v_id = vId;
  obj.service_name = serviceName;
  obj.required_privacy_standard = requiredPrivacyStandard;
  obj.data_type = dataType;
  obj.interval = interval;
  if (!obj.create()) {
    return ServiceInfo();
  }
  return ServiceInfo(obj);
}

ServiceInfo ServiceInfo::create(const QVariantMap &values)
{
  ServiceInfo model;
  model.setProperties(values);
  if (!model.d->create()) {
    model.d->clear();
  }
  return model;
}

QList<ServiceInfo> ServiceInfo::create(const QList<QVariantMap> &serviceInfoList){
  TSqlQueryORMapper<ServiceInfoObject> mapperQuery;
  mapperQuery.prepare(
      "INSERT INTO service_info"
      "(v_id, service_name, required_privacy_standard, data_type, interval)"
      "VALUES (?, ?, ?, ?, ?) returning *");
  QList<ServiceInfo> createdServiceInfoList;
  for (QVariantMap serviceInfo : serviceInfoList) {
    mapperQuery.addBind(serviceInfo["vId"].toInt());
    mapperQuery.addBind(serviceInfo["serviceName"].toString());
    mapperQuery.addBind(serviceInfo["requiredPrivacyStandard"].toInt());
    mapperQuery.addBind(serviceInfo["dataType"].toInt());
    mapperQuery.addBind(serviceInfo["interval"].toInt());
    if (mapperQuery.exec() && mapperQuery.next()){
      createdServiceInfoList.append(ServiceInfo(mapperQuery.value()));
    }
  }

  return createdServiceInfoList;
}

ServiceInfo ServiceInfo::get(int id)
{
  TSqlORMapper<ServiceInfoObject> mapper;
  return ServiceInfo(mapper.findByPrimaryKey(id));
}

QList<ServiceInfo> ServiceInfo::getByVid(int vId)
{
  TSqlORMapper<ServiceInfoObject> mapper;
  TCriteria crt(ServiceInfoObject::VId, vId);
  QList<ServiceInfo> serviceInfoList;
  if (mapper.find(crt) > 0) {
    for (TSqlORMapperIterator<ServiceInfoObject> i(mapper); i.hasNext(); ) {
      serviceInfoList.append((ServiceInfo(i.next())));
    }
  }
  return serviceInfoList;
}

QList<ServiceInfo> ServiceInfo::getForMatch(int dataType, int privacyStandard, int interval)
{
  TSqlORMapper<ServiceInfoObject> mapper;
  TCriteria crt(ServiceInfoObject::DataType, dataType);
  crt.add(ServiceInfoObject::RequiredPrivacyStandard, TSql::GreaterEqual, privacyStandard);
  crt.add(ServiceInfoObject::Interval, TSql::GreaterEqual, interval);
  QList<ServiceInfo> serviceInfoList;
  if (mapper.find(crt) > 0) {
    for (TSqlORMapperIterator<ServiceInfoObject> i(mapper); i.hasNext(); ) {
      serviceInfoList.append((ServiceInfo(i.next())));
    }
  }
  return serviceInfoList;
}

int ServiceInfo::count()
{
  TSqlORMapper<ServiceInfoObject> mapper;
  return mapper.findCount();
}

QList<ServiceInfo> ServiceInfo::getAll()
{
  return tfGetModelListByCriteria<ServiceInfo, ServiceInfoObject>(TCriteria());
}

QJsonArray ServiceInfo::getAllJson()
{
  QJsonArray array;
  TSqlORMapper<ServiceInfoObject> mapper;

  if (mapper.find() > 0) {
    for (TSqlORMapperIterator<ServiceInfoObject> i(mapper); i.hasNext(); ) {
      array.append(QJsonValue(QJsonObject::fromVariantMap(ServiceInfo(i.next()).toVariantMap())));
    }
  }
  return array;
}

TModelObject *ServiceInfo::modelData()
{
  return d.data();
}

const TModelObject *ServiceInfo::modelData() const
{
  return d.data();
}

QDataStream &operator<<(QDataStream &ds, const ServiceInfo &model)
{
  auto varmap = model.toVariantMap();
  ds << varmap;
  return ds;
}

QDataStream &operator>>(QDataStream &ds, ServiceInfo &model)
{
  QVariantMap varmap;
  ds >> varmap;
  model.setProperties(varmap);
  return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(ServiceInfo)
