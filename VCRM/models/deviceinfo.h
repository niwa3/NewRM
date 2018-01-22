#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class DeviceInfoObject;
class QJsonArray;


class T_MODEL_EXPORT DeviceInfo : public TAbstractModel
{
public:
    DeviceInfo();
    DeviceInfo(const DeviceInfo &other);
    DeviceInfo(const DeviceInfoObject &object);
    ~DeviceInfo();

    int id() const;
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    int cId() const;
    void setCId(int cId);
    QString deviceName() const;
    void setDeviceName(const QString &deviceName);
    int defaultPrivacyStandard() const;
    void setDefaultPrivacyStandard(int defaultPrivacyStandard);
    int deviceType() const;
    void setDeviceType(int deviceType);
    int dataType() const;
    void setDataType(int dataType);
    int interval() const;
    void setInterval(int interval);
    QString location() const;
    void setLocation(const QString &location);
    DeviceInfo &operator=(const DeviceInfo &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static DeviceInfo create(int cId, const QString &deviceName, int defaultPrivacyStandard, int deviceType, int dataType, int interval, const QString &location);
    static DeviceInfo create(const QVariantMap &values);
    static DeviceInfo get(int id);
    static QList<DeviceInfo> getByCid(int cId);
    static QList<DeviceInfo> getForMatch(int dataType, int privacyStandard, int interval);
    static int count();
    static QList<DeviceInfo> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<DeviceInfoObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const DeviceInfo &model);
    friend QDataStream &operator>>(QDataStream &ds, DeviceInfo &model);
};

Q_DECLARE_METATYPE(DeviceInfo)
Q_DECLARE_METATYPE(QList<DeviceInfo>)

#endif // DEVICEINFO_H
