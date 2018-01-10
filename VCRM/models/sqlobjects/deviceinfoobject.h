#ifndef DEVICEINFOOBJECT_H
#define DEVICEINFOOBJECT_H

#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT DeviceInfoObject : public TSqlObject, public QSharedData
{
public:
    int id {0};
    QDateTime created_at;
    QDateTime updated_at;
    int c_id {0};
    QString device_name;
    int default_privacy_standard {0};
    int device_type {0};
    int data_type {0};
    int interval {0};
    QString location;

    enum PropertyIndex {
        Id = 0,
        CreatedAt,
        UpdatedAt,
        CId,
        DeviceName,
        DefaultPrivacyStandard,
        DeviceType,
        DataType,
        Interval,
        Location,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return Id; }
    QString tableName() const override { return QLatin1String("device_info"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int id READ getid WRITE setid)
    T_DEFINE_PROPERTY(int, id)
    Q_PROPERTY(QDateTime created_at READ getcreated_at WRITE setcreated_at)
    T_DEFINE_PROPERTY(QDateTime, created_at)
    Q_PROPERTY(QDateTime updated_at READ getupdated_at WRITE setupdated_at)
    T_DEFINE_PROPERTY(QDateTime, updated_at)
    Q_PROPERTY(int c_id READ getc_id WRITE setc_id)
    T_DEFINE_PROPERTY(int, c_id)
    Q_PROPERTY(QString device_name READ getdevice_name WRITE setdevice_name)
    T_DEFINE_PROPERTY(QString, device_name)
    Q_PROPERTY(int default_privacy_standard READ getdefault_privacy_standard WRITE setdefault_privacy_standard)
    T_DEFINE_PROPERTY(int, default_privacy_standard)
    Q_PROPERTY(int device_type READ getdevice_type WRITE setdevice_type)
    T_DEFINE_PROPERTY(int, device_type)
    Q_PROPERTY(int data_type READ getdata_type WRITE setdata_type)
    T_DEFINE_PROPERTY(int, data_type)
    Q_PROPERTY(int interval READ getinterval WRITE setinterval)
    T_DEFINE_PROPERTY(int, interval)
    Q_PROPERTY(QString location READ getlocation WRITE setlocation)
    T_DEFINE_PROPERTY(QString, location)
};

#endif // DEVICEINFOOBJECT_H
