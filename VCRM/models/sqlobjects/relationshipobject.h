#ifndef RELATIONSHIPOBJECT_H
#define RELATIONSHIPOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT RelationshipObject : public TSqlObject, public QSharedData
{
public:
    int id {0};
    QDateTime created_at;
    QDateTime updated_at;
    int d_id {0};
    QString device_name;
    int s_id {0};
    QString service_name;
    int anonymity_method {0};
    int privacy_standard {0};
    int interval {0};
    QString location;

    enum PropertyIndex {
        Id = 0,
        CreatedAt,
        UpdatedAt,
        DId,
        DeviceName,
        SId,
        ServiceName,
        AnonymityMethod,
        PrivacyStandard,
        Interval,
        Location,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return Id; }
    QString tableName() const override { return QLatin1String("relationship"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int id READ getid WRITE setid)
    T_DEFINE_PROPERTY(int, id)
    Q_PROPERTY(QDateTime created_at READ getcreated_at WRITE setcreated_at)
    T_DEFINE_PROPERTY(QDateTime, created_at)
    Q_PROPERTY(QDateTime updated_at READ getupdated_at WRITE setupdated_at)
    T_DEFINE_PROPERTY(QDateTime, updated_at)
    Q_PROPERTY(int d_id READ getd_id WRITE setd_id)
    T_DEFINE_PROPERTY(int, d_id)
    Q_PROPERTY(QString device_name READ getdevice_name WRITE setdevice_name)
    T_DEFINE_PROPERTY(QString, device_name)
    Q_PROPERTY(int s_id READ gets_id WRITE sets_id)
    T_DEFINE_PROPERTY(int, s_id)
    Q_PROPERTY(QString service_name READ getservice_name WRITE setservice_name)
    T_DEFINE_PROPERTY(QString, service_name)
    Q_PROPERTY(int anonymity_method READ getanonymity_method WRITE setanonymity_method)
    T_DEFINE_PROPERTY(int, anonymity_method)
    Q_PROPERTY(int privacy_standard READ getprivacy_standard WRITE setprivacy_standard)
    T_DEFINE_PROPERTY(int, privacy_standard)
    Q_PROPERTY(int interval READ getinterval WRITE setinterval)
    T_DEFINE_PROPERTY(int, interval)
    Q_PROPERTY(QString location READ getlocation WRITE setlocation)
    T_DEFINE_PROPERTY(QString, location)
};

#endif // RELATIONSHIPOBJECT_H
