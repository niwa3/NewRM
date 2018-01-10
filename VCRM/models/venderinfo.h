#ifndef VENDERINFO_H
#define VENDERINFO_H

#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class VenderInfoObject;
class QJsonArray;


class T_MODEL_EXPORT VenderInfo : public TAbstractModel
{
public:
    VenderInfo();
    VenderInfo(const VenderInfo &other);
    VenderInfo(const VenderInfoObject &object);
    ~VenderInfo();

    int id() const;
    QDateTime createdAt() const;
    QDateTime updatedAt() const;
    int lId() const;
    void setLId(int lId);
    QString name() const;
    void setName(const QString &name);
    QString phoneNum() const;
    void setPhoneNum(const QString &phoneNum);
    QString eMailAddr() const;
    void setEMailAddr(const QString &eMailAddr);
    VenderInfo &operator=(const VenderInfo &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static VenderInfo create(int lId, const QString &name, const QString &phoneNum, const QString &eMailAddr);
    static VenderInfo create(const QVariantMap &values);
    static VenderInfo get(int id);
    static int count();
    static QList<VenderInfo> getAll();
    static QJsonArray getAllJson();

private:
    QSharedDataPointer<VenderInfoObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend QDataStream &operator<<(QDataStream &ds, const VenderInfo &model);
    friend QDataStream &operator>>(QDataStream &ds, VenderInfo &model);
};

Q_DECLARE_METATYPE(VenderInfo)
Q_DECLARE_METATYPE(QList<VenderInfo>)

#endif // VENDERINFO_H
