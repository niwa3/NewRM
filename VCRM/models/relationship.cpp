#include <treefrog/TreeFrogModel>
#include "relationship.h"
#include "relationshipobject.h"

Relationship::Relationship()
  : TAbstractModel(), d(new RelationshipObject())
{
  d->id = 0;
  d->d_id = 0;
  d->s_id = 0;
  d->anonymity_method = 0;
  d->privacy_standard = 0;
  d->interval = 0;
}

Relationship::Relationship(const Relationship &other)
  : TAbstractModel(), d(new RelationshipObject(*other.d))
{ }

Relationship::Relationship(const RelationshipObject &object)
  : TAbstractModel(), d(new RelationshipObject(object))
{ }

Relationship::~Relationship()
{
  // If the reference count becomes 0,
  // the shared data object 'RelationshipObject' is deleted.
}

int Relationship::id() const
{
  return d->id;
}

QDateTime Relationship::createdAt() const
{
  return d->created_at;
}

QDateTime Relationship::updatedAt() const
{
  return d->updated_at;
}

int Relationship::dId() const
{
  return d->d_id;
}

void Relationship::setDId(int dId)
{
  d->d_id = dId;
}

QString Relationship::deviceName() const
{
  return d->device_name;
}

void Relationship::setDeviceName(const QString &deviceName)
{
  d->device_name = deviceName;
}

int Relationship::sId() const
{
  return d->s_id;
}

void Relationship::setSId(int sId)
{
  d->s_id = sId;
}

QString Relationship::serviceName() const
{
  return d->service_name;
}

void Relationship::setServiceName(const QString &serviceName)
{
  d->service_name = serviceName;
}

int Relationship::anonymityMethod() const
{
  return d->anonymity_method;
}

void Relationship::setAnonymityMethod(int anonymityMethod)
{
  d->anonymity_method = anonymityMethod;
}

int Relationship::privacyStandard() const
{
  return d->privacy_standard;
}

void Relationship::setPrivacyStandard(int privacyStandard)
{
  d->privacy_standard = privacyStandard;
}

int Relationship::interval() const
{
  return d->interval;
}

void Relationship::setInterval(int interval)
{
  d->interval = interval;
}

QString Relationship::location() const
{
  return d->location;
}

void Relationship::setLocation(const QString &location)
{
  d->location = location;
}

Relationship &Relationship::operator=(const Relationship &other)
{
  d = other.d;  // increments the reference count of the data
  return *this;
}

Relationship Relationship::create(int dId, const QString &deviceName, int sId, const QString &serviceName, int anonymityMethod, int privacyStandard, int interval, const QString &location)
{
  RelationshipObject obj;
  obj.d_id = dId;
  obj.device_name = deviceName;
  obj.s_id = sId;
  obj.service_name = serviceName;
  obj.anonymity_method = anonymityMethod;
  obj.privacy_standard = privacyStandard;
  obj.interval = interval;
  obj.location = location;
  if (!obj.create()) {
    return Relationship();
  }
  return Relationship(obj);
}

Relationship Relationship::create(const QVariantMap &values)
{
  Relationship model;
  model.setProperties(values);
  if (!model.d->create()) {
    model.d->clear();
  }
  return model;
}

QList<Relationship> Relationship::create(const QList<QVariantMap> &relationshipList)
{
  TSqlQueryORMapper<RelationshipObject> mapperQuery;
  QString VALUES;
  int listNum = relationshipList.length();
  for (int i = 0 ; i < listNum-1; ++i) {
    QVariantMap relationship = relationshipList.at(i);
    VALUES += QStringLiteral("(%1, %2, %3, %4, %5, %6, %7, %8), ")
      .arg(TSqlQuery::formatValue(relationship["dId"].toInt()))
      .arg(TSqlQuery::formatValue(relationship["deviceName"].toString()))
      .arg(TSqlQuery::formatValue(relationship["sId"].toInt()))
      .arg(TSqlQuery::formatValue(relationship["serviceName"].toString()))
      .arg(TSqlQuery::formatValue(relationship["anonymityMethod"].toInt()))
      .arg(TSqlQuery::formatValue(relationship["privacyStandard"].toInt()))
      .arg(TSqlQuery::formatValue(relationship["interval"].toInt()))
      .arg(TSqlQuery::formatValue(relationship["location"].toString()));
  }
  QVariantMap lastRelationship = relationshipList.at(listNum-1);
  VALUES += QStringLiteral("(%1, %2, %3, %4, %5, %6, %7, %8)")
    .arg(TSqlQuery::formatValue(lastRelationship["dId"].toInt()))
    .arg(TSqlQuery::formatValue(lastRelationship["deviceName"].toString()))
    .arg(TSqlQuery::formatValue(lastRelationship["sId"].toInt()))
    .arg(TSqlQuery::formatValue(lastRelationship["serviceName"].toString()))
    .arg(TSqlQuery::formatValue(lastRelationship["anonymityMethod"].toInt()))
    .arg(TSqlQuery::formatValue(lastRelationship["privacyStandard"].toInt()))
    .arg(TSqlQuery::formatValue(lastRelationship["interval"].toInt()))
    .arg(TSqlQuery::formatValue(lastRelationship["location"].toString()));
  QString QUERY = 
      "INSERT INTO relationship "
      "(d_id, device_name, s_id, service_name, anonymity_method, "
      "privacy_standard, interval, location) "
      "VALUES " + VALUES + " "
      "returning relationship.*";
  if (!mapperQuery.exec(QUERY)) {
    return QList<Relationship>();
  }
  QList<Relationship> createdRelationshipList;
  TSqlQueryORMapperIterator<RelationshipObject> it(mapperQuery);
  while (it.hasNext()) {
    RelationshipObject obj = it.next();
    createdRelationshipList.append(Relationship(obj));
  }
  return createdRelationshipList;
}


Relationship Relationship::insert(const QVariantMap &values)
{
  TSqlQueryORMapper<RelationshipObject> mapperQuery;
  QString VALUES;
  VALUES += QStringLiteral("(%1, %2, %3, %4, %5, %6, %7, %8, %9, %10, %11)")
    .arg(TSqlQuery::formatValue(values["id"].toInt()))
    .arg(TSqlQuery::formatValue(values["createdAt"].toString()))
    .arg(TSqlQuery::formatValue(values["updatedAt"].toString()))
    .arg(TSqlQuery::formatValue(values["dId"].toInt()))
    .arg(TSqlQuery::formatValue(values["deviceName"].toString()))
    .arg(TSqlQuery::formatValue(values["sId"].toInt()))
    .arg(TSqlQuery::formatValue(values["serviceName"].toString()))
    .arg(TSqlQuery::formatValue(values["anonymityMethod"].toInt()))
    .arg(TSqlQuery::formatValue(values["privacyStandard"].toInt()))
    .arg(TSqlQuery::formatValue(values["interval"].toInt()))
    .arg(TSqlQuery::formatValue(values["location"].toString()));
  QString QUERY = 
      "INSERT INTO relationship "
      "(id, created_at, updated_at, d_id, device_name, s_id, service_name, anonymity_method, "
      "privacy_standard, interval, location) "
      "VALUES " + VALUES + " "
      "returning relationship.*";
  if (!mapperQuery.exec(QUERY)) {
    return Relationship();
  }
  TSqlQueryORMapperIterator<RelationshipObject> it(mapperQuery);
  RelationshipObject obj = it.next();
  Relationship createdRelationship = Relationship(obj);
  return createdRelationship;
}


QList<Relationship> Relationship::insert(const QList<QVariantMap> &relationshipList)
{
  TSqlQueryORMapper<RelationshipObject> mapperQuery;
  QString VALUES;
  int listNum = relationshipList.length();
  for (int i = 0 ; i < listNum-1; ++i) {
    QVariantMap relationship = relationshipList.at(i);
    VALUES += QStringLiteral("(%1, %2, %3, %4, %5, %6, %7, %8, %9, %10, %11), ")
      .arg(TSqlQuery::formatValue(relationship["id"].toInt()))
      .arg(TSqlQuery::formatValue(relationship["createdAt"].toString()))
      .arg(TSqlQuery::formatValue(relationship["updatedAt"].toString()))
      .arg(TSqlQuery::formatValue(relationship["dId"].toInt()))
      .arg(TSqlQuery::formatValue(relationship["deviceName"].toString()))
      .arg(TSqlQuery::formatValue(relationship["sId"].toInt()))
      .arg(TSqlQuery::formatValue(relationship["serviceName"].toString()))
      .arg(TSqlQuery::formatValue(relationship["anonymityMethod"].toInt()))
      .arg(TSqlQuery::formatValue(relationship["privacyStandard"].toInt()))
      .arg(TSqlQuery::formatValue(relationship["interval"].toInt()))
      .arg(TSqlQuery::formatValue(relationship["location"].toString()));
  }
  QVariantMap lastRelationship = relationshipList.at(listNum-1);
  VALUES += QStringLiteral("(%1, %2, %3, %4, %5, %6, %7, %8, %9, %10, %11)")
    .arg(TSqlQuery::formatValue(lastRelationship["id"].toInt()))
    .arg(TSqlQuery::formatValue(lastRelationship["createdAt"].toString()))
    .arg(TSqlQuery::formatValue(lastRelationship["updatedAt"].toString()))
    .arg(TSqlQuery::formatValue(lastRelationship["dId"].toInt()))
    .arg(TSqlQuery::formatValue(lastRelationship["deviceName"].toString()))
    .arg(TSqlQuery::formatValue(lastRelationship["sId"].toInt()))
    .arg(TSqlQuery::formatValue(lastRelationship["serviceName"].toString()))
    .arg(TSqlQuery::formatValue(lastRelationship["anonymityMethod"].toInt()))
    .arg(TSqlQuery::formatValue(lastRelationship["privacyStandard"].toInt()))
    .arg(TSqlQuery::formatValue(lastRelationship["interval"].toInt()))
    .arg(TSqlQuery::formatValue(lastRelationship["location"].toString()));
  QString QUERY = 
      "INSERT INTO relationship "
      "(id, created_at, updated_at, d_id, device_name, s_id, service_name, anonymity_method, "
      "privacy_standard, interval, location) "
      "VALUES " + VALUES + " "
      "returning relationship.*";
  if (!mapperQuery.exec(QUERY)) {
    return QList<Relationship>();
  }
  QList<Relationship> createdRelationshipList;
  TSqlQueryORMapperIterator<RelationshipObject> it(mapperQuery);
  while (it.hasNext()) {
    RelationshipObject obj = it.next();
    createdRelationshipList.append(Relationship(obj));
  }
  return createdRelationshipList;
}


Relationship Relationship::get(int id)
{
  TSqlORMapper<RelationshipObject> mapper;
  return Relationship(mapper.findByPrimaryKey(id));
}

int Relationship::count()
{
  TSqlORMapper<RelationshipObject> mapper;
  return mapper.findCount();
}

QList<Relationship> Relationship::getAll()
{
  return tfGetModelListByCriteria<Relationship, RelationshipObject>(TCriteria());
}

QJsonArray Relationship::getAllJson()
{
  QJsonArray array;
  TSqlORMapper<RelationshipObject> mapper;

  if (mapper.find() > 0) {
    for (TSqlORMapperIterator<RelationshipObject> i(mapper); i.hasNext(); ) {
      array.append(QJsonValue(QJsonObject::fromVariantMap(Relationship(i.next()).toVariantMap())));
    }
  }
  return array;
}

TModelObject *Relationship::modelData()
{
  return d.data();
}

const TModelObject *Relationship::modelData() const
{
  return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Relationship &model)
{
  auto varmap = model.toVariantMap();
  ds << varmap;
  return ds;
}

QDataStream &operator>>(QDataStream &ds, Relationship &model)
{
  QVariantMap varmap;
  ds >> varmap;
  model.setProperties(varmap);
  return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(Relationship)
