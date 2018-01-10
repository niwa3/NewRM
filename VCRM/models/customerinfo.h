#ifndef CUSTOMERINFO_H
#define CUSTOMERINFO_H

#include <QtCore/QStringList>
#include <QtCore/QDateTime>
#include <QtCore/QVariant>
#include <QtCore/QSharedDataPointer>
#include <treefrog/TGlobal>
#include <treefrog/TAbstractModel>
#include <treefrog/TreeFrogModel>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

class TModelObject;
class CustomerInfoObject;
class QJsonArray;


class T_MODEL_EXPORT CustomerInfo : public TAbstractModel
{
public:
    CustomerInfo();
    CustomerInfo(const CustomerInfo &other);
    CustomerInfo(const CustomerInfoObject &object);
    ~CustomerInfo();

    int id() const;
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    int lId() const;
    void setLId(int lId);
    QString lastName() const;
    void setLastName(const QString &lastName);
    QString firstName() const;
    void setFirstName(const QString &firstName);
    QDateTime birthday() const;
    void setBirthday(const QDateTime &birthday);
    QString eMailAddr() const;
    void setEMailAddr(const QString &eMailAddr);
    QString phoneNum() const;
    void setPhoneNum(const QString &phoneNum);
    CustomerInfo &operator=(const CustomerInfo &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static CustomerInfo create(int lId, const QString &lastName, const QString &firstName, const QDateTime &birthday, const QString &eMailAddr, const QString &phoneNum);
    static CustomerInfo create(const QVariantMap &values);
    static CustomerInfo get(int id);
    static CustomerInfo getByLid(int lId);
    static int count();
    static QList<CustomerInfo> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<CustomerInfoObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const CustomerInfo &model);
    friend QDataStream &operator>>(QDataStream &ds, CustomerInfo &model);
};

Q_DECLARE_METATYPE(CustomerInfo)
Q_DECLARE_METATYPE(QList<CustomerInfo>)

#endif // CUSTOMERINFO_H
