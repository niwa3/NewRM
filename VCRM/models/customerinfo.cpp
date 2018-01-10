#include "customerinfo.h"
#include "customerinfoobject.h"

CustomerInfo::CustomerInfo()
    : TAbstractModel(), d(new CustomerInfoObject())
{
    d->id = 0;
    d->l_id = 0;
}

CustomerInfo::CustomerInfo(const CustomerInfo &other)
    : TAbstractModel(), d(new CustomerInfoObject(*other.d))
{ }

CustomerInfo::CustomerInfo(const CustomerInfoObject &object)
    : TAbstractModel(), d(new CustomerInfoObject(object))
{ }

CustomerInfo::~CustomerInfo()
{
    // If the reference count becomes 0,
    // the shared data object 'CustomerInfoObject' is deleted.
}

int CustomerInfo::id() const
{
    return d->id;
}

QDateTime CustomerInfo::createdAt() const
{
    return d->created_at;
}

QDateTime CustomerInfo::updatedAt() const
{
    return d->updated_at;
}

int CustomerInfo::lId() const
{
    return d->l_id;
}

void CustomerInfo::setLId(int lId)
{
    d->l_id = lId;
}

QString CustomerInfo::lastName() const
{
    return d->last_name;
}

void CustomerInfo::setLastName(const QString &lastName)
{
    d->last_name = lastName;
}

QString CustomerInfo::firstName() const
{
    return d->first_name;
}

void CustomerInfo::setFirstName(const QString &firstName)
{
    d->first_name = firstName;
}

QDateTime CustomerInfo::birthday() const
{
    return d->birthday;
}

void CustomerInfo::setBirthday(const QDateTime &birthday)
{
    d->birthday = birthday;
}

QString CustomerInfo::eMailAddr() const
{
    return d->e_mail_addr;
}

void CustomerInfo::setEMailAddr(const QString &eMailAddr)
{
    d->e_mail_addr = eMailAddr;
}

QString CustomerInfo::phoneNum() const
{
    return d->phone_num;
}

void CustomerInfo::setPhoneNum(const QString &phoneNum)
{
    d->phone_num = phoneNum;
}

CustomerInfo &CustomerInfo::operator=(const CustomerInfo &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

CustomerInfo CustomerInfo::create(int lId, const QString &lastName, const QString &firstName, const QDateTime &birthday, const QString &eMailAddr, const QString &phoneNum)
{
    CustomerInfoObject obj;
    obj.l_id = lId;
    obj.last_name = lastName;
    obj.first_name = firstName;
    obj.birthday = birthday;
    obj.e_mail_addr = eMailAddr;
    obj.phone_num = phoneNum;
    if (!obj.create()) {
        return CustomerInfo();
    }
    return CustomerInfo(obj);
}

CustomerInfo CustomerInfo::create(const QVariantMap &values)
{
    CustomerInfo model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

CustomerInfo CustomerInfo::get(int id)
{
    TSqlORMapper<CustomerInfoObject> mapper;
    return CustomerInfo(mapper.findByPrimaryKey(id));
}

CustomerInfo CustomerInfo::getByLid(int lId)
{
    TSqlORMapper<CustomerInfoObject> mapper;
    TCriteria crt(CustomerInfoObject::LId, lId);
    //lIdはunique属性のため、１つのみがヒットするはず
    return CustomerInfo(mapper.findFirst(crt));
}

int CustomerInfo::count()
{
    TSqlORMapper<CustomerInfoObject> mapper;
    return mapper.findCount();
}

QList<CustomerInfo> CustomerInfo::getAll()
{
    return tfGetModelListByCriteria<CustomerInfo, CustomerInfoObject>(TCriteria());
}

QJsonArray CustomerInfo::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<CustomerInfoObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<CustomerInfoObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(CustomerInfo(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *CustomerInfo::modelData()
{
    return d.data();
}

const TModelObject *CustomerInfo::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const CustomerInfo &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, CustomerInfo &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(CustomerInfo)
