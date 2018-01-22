#include <TreeFrogModel>
#include "deviceinfo.h"
#include "deviceinfoobject.h"

DeviceInfo::DeviceInfo()
    : TAbstractModel(), d(new DeviceInfoObject())
{
    d->id = 0;
    d->c_id = 0;
    d->default_privacy_standard = 0;
    d->device_type = 0;
    d->data_type = 0;
    d->interval = 0;
}

DeviceInfo::DeviceInfo(const DeviceInfo &other)
    : TAbstractModel(), d(new DeviceInfoObject(*other.d))
{ }

DeviceInfo::DeviceInfo(const DeviceInfoObject &object)
    : TAbstractModel(), d(new DeviceInfoObject(object))
{ }

DeviceInfo::~DeviceInfo()
{
    // If the reference count becomes 0,
    // the shared data object 'DeviceInfoObject' is deleted.
}

int DeviceInfo::id() const
{
    return d->id;
}

QDateTime DeviceInfo::createdAt() const
{
    return d->created_at;
}

QDateTime DeviceInfo::updatedAt() const
{
    return d->updated_at;
}

int DeviceInfo::cId() const
{
    return d->c_id;
}

void DeviceInfo::setCId(int cId)
{
    d->c_id = cId;
}

QString DeviceInfo::deviceName() const
{
    return d->device_name;
}

void DeviceInfo::setDeviceName(const QString &deviceName)
{
    d->device_name = deviceName;
}

int DeviceInfo::defaultPrivacyStandard() const
{
    return d->default_privacy_standard;
}

void DeviceInfo::setDefaultPrivacyStandard(int defaultPrivacyStandard)
{
    d->default_privacy_standard = defaultPrivacyStandard;
}

int DeviceInfo::deviceType() const
{
    return d->device_type;
}

void DeviceInfo::setDeviceType(int deviceType)
{
    d->device_type = deviceType;
}

int DeviceInfo::dataType() const
{
    return d->data_type;
}

void DeviceInfo::setDataType(int dataType)
{
    d->data_type = dataType;
}

int DeviceInfo::interval() const
{
    return d->interval;
}

void DeviceInfo::setInterval(int interval)
{
    d->interval = interval;
}

QString DeviceInfo::location() const
{
    return d->location;
}

void DeviceInfo::setLocation(const QString &location)
{
    d->location = location;
}

DeviceInfo &DeviceInfo::operator=(const DeviceInfo &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

DeviceInfo DeviceInfo::create(int cId, const QString &deviceName, int defaultPrivacyStandard, int deviceType, int dataType, int interval, const QString &location)
{
    DeviceInfoObject obj;
    obj.c_id = cId;
    obj.device_name = deviceName;
    obj.default_privacy_standard = defaultPrivacyStandard;
    obj.device_type = deviceType;
    obj.data_type = dataType;
    obj.interval = interval;
    obj.location = location;
    if (!obj.create()) {
        return DeviceInfo();
    }
    return DeviceInfo(obj);
}

DeviceInfo DeviceInfo::create(const QVariantMap &values)
{
    DeviceInfo model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

DeviceInfo DeviceInfo::get(int id)
{
    TSqlORMapper<DeviceInfoObject> mapper;
    return DeviceInfo(mapper.findByPrimaryKey(id));
}

QList<DeviceInfo> DeviceInfo::getByCid(int cId)
{
    TSqlORMapper<DeviceInfoObject> mapper;
    TCriteria crt(DeviceInfoObject::CId, cId);
    QList<DeviceInfo> deviceInfoList;
    if (mapper.find(crt) > 0) {
        for (TSqlORMapperIterator<DeviceInfoObject> i(mapper); i.hasNext(); ) {
            deviceInfoList.append((DeviceInfo(i.next())));
        }
    }
    return deviceInfoList;
}

QList<DeviceInfo> DeviceInfo::getForMatch(int dataType, int privacyStandard, int interval)
{
    TSqlORMapper<DeviceInfoObject> mapper;
    TCriteria crt(DeviceInfoObject::DataType, dataType);
    crt.add(DeviceInfoObject::DefaultPrivacyStandard, TSql::LessEqual, privacyStandard);
    crt.add(DeviceInfoObject::Interval, TSql::LessEqual, interval);
    QList<DeviceInfo> deviceInfoList;
    if (mapper.find(crt) > 0) {
        for (TSqlORMapperIterator<DeviceInfoObject> i(mapper); i.hasNext(); ) {
            deviceInfoList.append((DeviceInfo(i.next())));
        }
    }
    return deviceInfoList;
}

int DeviceInfo::count()
{
    TSqlORMapper<DeviceInfoObject> mapper;
    return mapper.findCount();
}

QList<DeviceInfo> DeviceInfo::getAll()
{
    return tfGetModelListByCriteria<DeviceInfo, DeviceInfoObject>(TCriteria());
}

QJsonArray DeviceInfo::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<DeviceInfoObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<DeviceInfoObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(DeviceInfo(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *DeviceInfo::modelData()
{
    return d.data();
}

const TModelObject *DeviceInfo::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const DeviceInfo &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, DeviceInfo &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(DeviceInfo)
