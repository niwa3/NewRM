#ifndef VENDERINFOOBJECT_H
#define VENDERINFOOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT VenderInfoObject : public TSqlObject, public QSharedData
{
public:
    int id {0};
    QDateTime created_at;
    QDateTime updated_at;
    int l_id {0};
    QString name;
    QString phone_num;
    QString e_mail_addr;

    enum PropertyIndex {
        Id = 0,
        CreatedAt,
        UpdatedAt,
        LId,
        Name,
        PhoneNum,
        EMailAddr,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return Id; }
    QString tableName() const override { return QLatin1String("vender_info"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int id READ getid WRITE setid)
    T_DEFINE_PROPERTY(int, id)
    Q_PROPERTY(QDateTime created_at READ getcreated_at WRITE setcreated_at)
    T_DEFINE_PROPERTY(QDateTime, created_at)
    Q_PROPERTY(QDateTime updated_at READ getupdated_at WRITE setupdated_at)
    T_DEFINE_PROPERTY(QDateTime, updated_at)
    Q_PROPERTY(int l_id READ getl_id WRITE setl_id)
    T_DEFINE_PROPERTY(int, l_id)
    Q_PROPERTY(QString name READ getname WRITE setname)
    T_DEFINE_PROPERTY(QString, name)
    Q_PROPERTY(QString phone_num READ getphone_num WRITE setphone_num)
    T_DEFINE_PROPERTY(QString, phone_num)
    Q_PROPERTY(QString e_mail_addr READ gete_mail_addr WRITE sete_mail_addr)
    T_DEFINE_PROPERTY(QString, e_mail_addr)
};

#endif // VENDERINFOOBJECT_H
