#ifndef LOGININFOOBJECT_H
#define LOGININFOOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT LoginInfoObject : public TSqlObject, public QSharedData
{
public:
    int id {0};
    QDateTime created_at;
    QDateTime updated_at;
    QString login;
    QString passwd;
    QString salt;
    int user_type {0};

    enum PropertyIndex {
        Id = 0,
        CreatedAt,
        UpdatedAt,
        Login,
        Passwd,
        Salt,
        UserType,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return Id; }
    QString tableName() const override { return QLatin1String("login_info"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int id READ getid WRITE setid)
    T_DEFINE_PROPERTY(int, id)
    Q_PROPERTY(QDateTime created_at READ getcreated_at WRITE setcreated_at)
    T_DEFINE_PROPERTY(QDateTime, created_at)
    Q_PROPERTY(QDateTime updated_at READ getupdated_at WRITE setupdated_at)
    T_DEFINE_PROPERTY(QDateTime, updated_at)
    Q_PROPERTY(QString login READ getlogin WRITE setlogin)
    T_DEFINE_PROPERTY(QString, login)
    Q_PROPERTY(QString passwd READ getpasswd WRITE setpasswd)
    T_DEFINE_PROPERTY(QString, passwd)
    Q_PROPERTY(QString salt READ getsalt WRITE setsalt)
    T_DEFINE_PROPERTY(QString, salt)
    Q_PROPERTY(int user_type READ getuser_type WRITE setuser_type)
    T_DEFINE_PROPERTY(int, user_type)
};

#endif // LOGININFOOBJECT_H
