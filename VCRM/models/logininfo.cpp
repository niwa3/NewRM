#include <TreeFrogModel>
#include "logininfo.h"
#include "logininfoobject.h"

LoginInfo::LoginInfo()
    : TAbstractModel(), d(new LoginInfoObject())
{
    d->id = 0;
    d->user_type = 0;
}

LoginInfo::LoginInfo(const LoginInfo &other)
    : TAbstractModel(), d(new LoginInfoObject(*other.d))
{ }

LoginInfo::LoginInfo(const LoginInfoObject &object)
    : TAbstractModel(), d(new LoginInfoObject(object))
{ }

LoginInfo::~LoginInfo()
{
    // If the reference count becomes 0,
    // the shared data object 'LoginInfoObject' is deleted.
}

int LoginInfo::id() const
{
    return d->id;
}

QDateTime LoginInfo::createdAt() const
{
    return d->created_at;
}

QDateTime LoginInfo::updatedAt() const
{
    return d->updated_at;
}

QString LoginInfo::login() const
{
    return d->login;
}

void LoginInfo::setLogin(const QString &login)
{
    d->login = login;
}

QString LoginInfo::passwd() const
{
    return d->passwd;
}

void LoginInfo::setPasswd(const QString &passwd)
{
    d->passwd = passwd;
}

QString LoginInfo::salt() const
{
    return d->salt;
}

void LoginInfo::setSalt(const QString &salt)
{
    d->salt = salt;
}

int LoginInfo::userType() const
{
    return d->user_type;
}

void LoginInfo::setUserType(int userType)
{
    d->user_type = userType;
}

LoginInfo &LoginInfo::operator=(const LoginInfo &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

LoginInfo LoginInfo::create(const QString &login, const QString &passwd, const QString &salt, int userType)
{
    LoginInfoObject obj;
    obj.login = login;
    obj.passwd = passwd;
    obj.salt = salt;
    obj.user_type = userType;
    if (!obj.create()) {
        return LoginInfo();
    }
    return LoginInfo(obj);
}

LoginInfo LoginInfo::create(const QVariantMap &values)
{
    LoginInfo model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

LoginInfo LoginInfo::get(int id)
{
    TSqlORMapper<LoginInfoObject> mapper;
    return LoginInfo(mapper.findByPrimaryKey(id));
}

int LoginInfo::count()
{
    TSqlORMapper<LoginInfoObject> mapper;
    return mapper.findCount();
}

QList<LoginInfo> LoginInfo::getAll()
{
    return tfGetModelListByCriteria<LoginInfo, LoginInfoObject>(TCriteria());
}

QJsonArray LoginInfo::getAllJson()
{
    QJsonArray array;
    TSqlORMapper<LoginInfoObject> mapper;

    if (mapper.find() > 0) {
        for (TSqlORMapperIterator<LoginInfoObject> i(mapper); i.hasNext(); ) {
            array.append(QJsonValue(QJsonObject::fromVariantMap(LoginInfo(i.next()).toVariantMap())));
        }
    }
    return array;
}

TModelObject *LoginInfo::modelData()
{
    return d.data();
}

const TModelObject *LoginInfo::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const LoginInfo &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, LoginInfo &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}

// Don't remove below this line
T_REGISTER_STREAM_OPERATORS(LoginInfo)
