#ifndef LOGININFO_H
#define LOGININFO_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class LoginInfoObject;
class QJsonArray;


class T_MODEL_EXPORT LoginInfo : public TAbstractModel
{
public:
    LoginInfo();
    LoginInfo(const LoginInfo &other);
    LoginInfo(const LoginInfoObject &object);
    ~LoginInfo();

    int id() const;
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    QString login() const;
    void setLogin(const QString &login);
    QString passwd() const;
    void setPasswd(const QString &passwd);
    QString salt() const;
    void setSalt(const QString &salt);
    int userType() const;
    void setUserType(int userType);
    LoginInfo &operator=(const LoginInfo &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static LoginInfo create(const QString &login, const QString &passwd, const QString &salt, int userType);
    static LoginInfo create(const QVariantMap &values);
    static LoginInfo get(int id);
    static int count();
    static QList<LoginInfo> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<LoginInfoObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const LoginInfo &model);
    friend QDataStream &operator>>(QDataStream &ds, LoginInfo &model);
};

Q_DECLARE_METATYPE(LoginInfo)
Q_DECLARE_METATYPE(QList<LoginInfo>)

#endif // LOGININFO_H
