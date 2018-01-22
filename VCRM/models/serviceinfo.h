#ifndef SERVICEINFO_H
#define SERVICEINFO_H

#include <QtCore/QStringList>
#include <QtCore/QDateTime>
#include <QtCore/QVariant>
#include <QtCore/QSharedDataPointer>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <treefrog/TGlobal>
#include <treefrog/TAbstractModel>

class TModelObject;
class ServiceInfoObject;
class QJsonArray;


class T_MODEL_EXPORT ServiceInfo : public TAbstractModel
{
public:
  ServiceInfo();
  ServiceInfo(const ServiceInfo &other);
  ServiceInfo(const ServiceInfoObject &object);
  ~ServiceInfo();

  int id() const;
  QDateTime createdAt() const;
  QDateTime updatedAt() const;
  int vId() const;
  void setVId(int vId);
  QString serviceName() const;
  void setServiceName(const QString &serviceName);
  int requiredPrivacyStandard() const;
  void setRequiredPrivacyStandard(int requiredPrivacyStandard);
  int dataType() const;
  void setDataType(int dataType);
  int interval() const;
  void setInterval(int interval);
  ServiceInfo &operator=(const ServiceInfo &other);

  bool create() override { return TAbstractModel::create(); }
  bool update() override { return TAbstractModel::update(); }
  bool save()   override { return TAbstractModel::save(); }
  bool remove() override { return TAbstractModel::remove(); }

  static ServiceInfo create(int vId, const QString &serviceName, int requiredPrivacyStandard, int dataType, int interval);
  static ServiceInfo create(const QVariantMap &values);
  static QList<ServiceInfo> create(const QList<QVariantMap> &serviceInfoList);
  static ServiceInfo get(int id);
  static QList<ServiceInfo> getByVid(int vId);
  static QList<ServiceInfo> getForMatch(int dataType, int privacyStandard, int interval);
  static int count();
  static QList<ServiceInfo> getAll();
  static QJsonArray getAllJson();

private:
  QSharedDataPointer<ServiceInfoObject> d;

  TModelObject *modelData() override;
  const TModelObject *modelData() const override;
  friend QDataStream &operator<<(QDataStream &ds, const ServiceInfo &model);
  friend QDataStream &operator>>(QDataStream &ds, ServiceInfo &model);
};

Q_DECLARE_METATYPE(ServiceInfo)
Q_DECLARE_METATYPE(QList<ServiceInfo>)

#endif // SERVICEINFO_H
