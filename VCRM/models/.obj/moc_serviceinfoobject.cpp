/****************************************************************************
** Meta object code from reading C++ file 'serviceinfoobject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sqlobjects/serviceinfoobject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serviceinfoobject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ServiceInfoObject_t {
    QByteArrayData data[9];
    char stringdata[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ServiceInfoObject_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ServiceInfoObject_t qt_meta_stringdata_ServiceInfoObject = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 2),
QT_MOC_LITERAL(2, 21, 10),
QT_MOC_LITERAL(3, 32, 10),
QT_MOC_LITERAL(4, 43, 4),
QT_MOC_LITERAL(5, 48, 12),
QT_MOC_LITERAL(6, 61, 25),
QT_MOC_LITERAL(7, 87, 9),
QT_MOC_LITERAL(8, 97, 8)
    },
    "ServiceInfoObject\0id\0created_at\0"
    "updated_at\0v_id\0service_name\0"
    "required_privacy_standard\0data_type\0"
    "interval"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ServiceInfoObject[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       8,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::Int, 0x00095003,
       2, QMetaType::QDateTime, 0x00095003,
       3, QMetaType::QDateTime, 0x00095003,
       4, QMetaType::Int, 0x00095003,
       5, QMetaType::QString, 0x00095003,
       6, QMetaType::Int, 0x00095003,
       7, QMetaType::Int, 0x00095003,
       8, QMetaType::Int, 0x00095003,

       0        // eod
};

void ServiceInfoObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ServiceInfoObject::staticMetaObject = {
    { &TSqlObject::staticMetaObject, qt_meta_stringdata_ServiceInfoObject.data,
      qt_meta_data_ServiceInfoObject,  qt_static_metacall, 0, 0}
};


const QMetaObject *ServiceInfoObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServiceInfoObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ServiceInfoObject.stringdata))
        return static_cast<void*>(const_cast< ServiceInfoObject*>(this));
    if (!strcmp(_clname, "QSharedData"))
        return static_cast< QSharedData*>(const_cast< ServiceInfoObject*>(this));
    return TSqlObject::qt_metacast(_clname);
}

int ServiceInfoObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TSqlObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = getid(); break;
        case 1: *reinterpret_cast< QDateTime*>(_v) = getcreated_at(); break;
        case 2: *reinterpret_cast< QDateTime*>(_v) = getupdated_at(); break;
        case 3: *reinterpret_cast< int*>(_v) = getv_id(); break;
        case 4: *reinterpret_cast< QString*>(_v) = getservice_name(); break;
        case 5: *reinterpret_cast< int*>(_v) = getrequired_privacy_standard(); break;
        case 6: *reinterpret_cast< int*>(_v) = getdata_type(); break;
        case 7: *reinterpret_cast< int*>(_v) = getinterval(); break;
        default: break;
        }
        _id -= 8;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setid(*reinterpret_cast< int*>(_v)); break;
        case 1: setcreated_at(*reinterpret_cast< QDateTime*>(_v)); break;
        case 2: setupdated_at(*reinterpret_cast< QDateTime*>(_v)); break;
        case 3: setv_id(*reinterpret_cast< int*>(_v)); break;
        case 4: setservice_name(*reinterpret_cast< QString*>(_v)); break;
        case 5: setrequired_privacy_standard(*reinterpret_cast< int*>(_v)); break;
        case 6: setdata_type(*reinterpret_cast< int*>(_v)); break;
        case 7: setinterval(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
        _id -= 8;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 8;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
