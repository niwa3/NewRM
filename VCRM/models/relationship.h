#ifndef RELATIONSHIP_H
#define RELATIONSHIP_H

#include <QtCore/QStringList>
#include <QtCore/QDateTime>
#include <QtCore/QVariant>
#include <QtCore/QSharedDataPointer>
#include <treefrog/TGlobal>
#include <treefrog/TAbstractModel>
#include <treefrog/TSqlORMapper>
#include <treefrog/TSqlORMapperIterator>
class TModelObject;
class RelationshipObject;
class QJsonArray;


class T_MODEL_EXPORT Relationship : public TAbstractModel
{
public:
    Relationship();
    Relationship(const Relationship &other);
    Relationship(const RelationshipObject &object);
    ~Relationship();

    int id() const;
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    int dId() const;
    void setDId(int dId);
    QString deviceName() const;
    void setDeviceName(const QString &deviceName);
    int sId() const;
    void setSId(int sId);
    QString serviceName() const;
    void setServiceName(const QString &serviceName);
    int anonymityMethod() const;
    void setAnonymityMethod(int anonymityMethod);
    int privacyStandard() const;
    void setPrivacyStandard(int privacyStandard);
    int interval() const;
    void setInterval(int interval);
    QString location() const;
    void setLocation(const QString &location);
    Relationship &operator=(const Relationship &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Relationship create(int dId, const QString &deviceName, int sId, const QString &serviceName, int anonymityMethod, int privacyStandard, int interval, const QString &location);
    static Relationship create(const QVariantMap &values);
    static QList<Relationship> create(const QList<QVariantMap> &ralationList);
    static Relationship insert(const QVariantMap &values);
    static QList<Relationship> insert(const QList<QVariantMap> &relationList);
    static Relationship get(int id);
    static int count();
    static QList<Relationship> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<RelationshipObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const Relationship &model);
    friend QDataStream &operator>>(QDataStream &ds, Relationship &model);
};

Q_DECLARE_METATYPE(Relationship)
Q_DECLARE_METATYPE(QList<Relationship>)

#endif // RELATIONSHIP_H
