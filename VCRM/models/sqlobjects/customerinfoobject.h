#ifndef CUSTOMERINFOOBJECT_H
#define CUSTOMERINFOOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT CustomerInfoObject : public TSqlObject, public QSharedData
{
public:
    int id {0};
    QDateTime created_at;
    QDateTime updated_at;
    int l_id {0};
    QString last_name;
    QString first_name;
    QDateTime birthday;
    QString e_mail_addr;
    QString phone_num;

    enum PropertyIndex {
        Id = 0,
        CreatedAt,
        UpdatedAt,
        LId,
        LastName,
        FirstName,
        Birthday,
        EMailAddr,
        PhoneNum,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return Id; }
    QString tableName() const override { return QLatin1String("customer_info"); }

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
    Q_PROPERTY(QString last_name READ getlast_name WRITE setlast_name)
    T_DEFINE_PROPERTY(QString, last_name)
    Q_PROPERTY(QString first_name READ getfirst_name WRITE setfirst_name)
    T_DEFINE_PROPERTY(QString, first_name)
    Q_PROPERTY(QDateTime birthday READ getbirthday WRITE setbirthday)
    T_DEFINE_PROPERTY(QDateTime, birthday)
    Q_PROPERTY(QString e_mail_addr READ gete_mail_addr WRITE sete_mail_addr)
    T_DEFINE_PROPERTY(QString, e_mail_addr)
    Q_PROPERTY(QString phone_num READ getphone_num WRITE setphone_num)
    T_DEFINE_PROPERTY(QString, phone_num)
};

#endif // CUSTOMERINFOOBJECT_H
