#include <TreeFrogModel>
#include "venderinfo.h"
#include "venderinfoobject.h"

VenderInfo::VenderInfo()
    : TAbstractModel(), d(new VenderInfoObject())
{
    d->id = 0;
    d->l_id = 0;
}

VenderInfo::VenderInfo(const VenderInfo &other)
    : TAbstractModel(), d(new VenderInfoObject(*other.d))
{ }

VenderInfo::VenderInfo(const VenderInfoObject &object)
    : TAbstractModel(), d(new VenderInfoObject(object))
{ }

VenderInfo::~VenderInfo()
{
    // If the reference count becomes 0,
    // the shared data object 'VenderInfoObject' is deleted.
}

int VenderInfo::id() const
{
    return d->id;
}

QDateTime VenderInfo::createdAt() const
{
    return d->created_at;
}

QDateTime VenderInfo::updatedAt() const
{
    return d->updated_at;
}

int VenderInfo::lId() const
{
    return d->l_id;
}

void VenderInfo::setLId(int lId)
{
    d->l_id = lId;
}

QString VenderInfo::name() const
{
    return d->name;
}

void VenderInfo::setName(const QString &name)
{
    d->name = name;
}

QString VenderInfo::phoneNum() const
{
    return d->phone_num;
}

void VenderInfo::setPhoneNum(const QString &phoneNum)
{
    d->phone_num = phoneNum;
}

QString VenderInfo::eMailAddr() const
{
    return d->e_mail_addr;
}

void VenderInfo::setEMailAddr(const QString &eMailAddr)
{
    d->e_mail_addr = eMailAddr;
}

VenderInfo &VenderInfo::operator=(const VenderInfo &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

VenderInfo VenderInfo::create(int lId, const QString &name, const QString &phoneNum, const QString &eMailAddr)
{
    VenderInfoObject obj;
    obj.l_id = lId;
    obj.name = name;
    obj.phone_num = phoneNum;
    obj.e_mail_addr = eMailAddr;
    if (!obj.create()) {
        return VenderInfo();
    }
    return VenderInfo(obj);
}

VenderInfo VenderInfo::create(const QVariantMap &values)
{
    VenderInfo model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

VenderInfo VenderInfo::get(int id)
{
    TSqlORMapper<VenderInfoObject> mapper;
    return VenderInfo(mapper.findByPrimaryKey(id));
}

int VenderInfo::count()
{
    TSqlORMapper<VenderInfoObject> mapper;
    return mapper.findCount();
}

QList<VenderInfo> VenderInfo::getAll()
{
    return tfGetModelListByCriteria<VenderInfo, VenderInfoObject>(TCriteria());
}

QJsonArray VenderInfo::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<VenderInfoObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<VenderInfoObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(VenderInfo(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *VenderInfo::modelData()
{
    return d.data();
}

const TModelObject *VenderInfo::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const VenderInfo &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, VenderInfo &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(VenderInfo)
