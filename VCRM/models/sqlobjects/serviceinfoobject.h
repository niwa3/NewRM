#ifndef SERVICEINFOOBJECT_H
#define SERVICEINFOOBJECT_H

#include <treefrog/TSqlObject>
#include <QtCore/QSharedData>


class T_MODEL_EXPORT ServiceInfoObject : public TSqlObject, public QSharedData
{
public:
    int id {0};
    QDateTime created_at;
    QDateTime updated_at;
    int v_id {0};
    QString service_name;
    int required_privacy_standard {0};
    int data_type {0};
    int interval {0};

    enum PropertyIndex {
        Id = 0,
        CreatedAt,
        UpdatedAt,
        VId,
        ServiceName,
        RequiredPrivacyStandard,
        DataType,
        Interval,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return Id; }
    QString tableName() const override { return QLatin1String("service_info"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int id READ getid WRITE setid)
    T_DEFINE_PROPERTY(int, id)
    Q_PROPERTY(QDateTime created_at READ getcreated_at WRITE setcreated_at)
    T_DEFINE_PROPERTY(QDateTime, created_at)
    Q_PROPERTY(QDateTime updated_at READ getupdated_at WRITE setupdated_at)
    T_DEFINE_PROPERTY(QDateTime, updated_at)
    Q_PROPERTY(int v_id READ getv_id WRITE setv_id)
    T_DEFINE_PROPERTY(int, v_id)
    Q_PROPERTY(QString service_name READ getservice_name WRITE setservice_name)
    T_DEFINE_PROPERTY(QString, service_name)
    Q_PROPERTY(int required_privacy_standard READ getrequired_privacy_standard WRITE setrequired_privacy_standard)
    T_DEFINE_PROPERTY(int, required_privacy_standard)
    Q_PROPERTY(int data_type READ getdata_type WRITE setdata_type)
    T_DEFINE_PROPERTY(int, data_type)
    Q_PROPERTY(int interval READ getinterval WRITE setinterval)
    T_DEFINE_PROPERTY(int, interval)
};

#endif // SERVICEINFOOBJECT_H
