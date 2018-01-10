/****************************************************************************
** Meta object code from reading C++ file 'customerinfoobject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sqlobjects/customerinfoobject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'customerinfoobject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CustomerInfoObject_t {
    QByteArrayData data[10];
    char stringdata[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CustomerInfoObject_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CustomerInfoObject_t qt_meta_stringdata_CustomerInfoObject = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 2),
QT_MOC_LITERAL(2, 22, 10),
QT_MOC_LITERAL(3, 33, 10),
QT_MOC_LITERAL(4, 44, 4),
QT_MOC_LITERAL(5, 49, 9),
QT_MOC_LITERAL(6, 59, 10),
QT_MOC_LITERAL(7, 70, 8),
QT_MOC_LITERAL(8, 79, 11),
QT_MOC_LITERAL(9, 91, 9)
    },
    "CustomerInfoObject\0id\0created_at\0"
    "updated_at\0l_id\0last_name\0first_name\0"
    "birthday\0e_mail_addr\0phone_num"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CustomerInfoObject[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       9,   14, // properties
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
       6, QMetaType::QString, 0x00095003,
       7, QMetaType::QDateTime, 0x00095003,
       8, QMetaType::QString, 0x00095003,
       9, QMetaType::QString, 0x00095003,

       0        // eod
};

void CustomerInfoObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject CustomerInfoObject::staticMetaObject = {
    { &TSqlObject::staticMetaObject, qt_meta_stringdata_CustomerInfoObject.data,
      qt_meta_data_CustomerInfoObject,  qt_static_metacall, 0, 0}
};


const QMetaObject *CustomerInfoObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomerInfoObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CustomerInfoObject.stringdata))
        return static_cast<void*>(const_cast< CustomerInfoObject*>(this));
    if (!strcmp(_clname, "QSharedData"))
        return static_cast< QSharedData*>(const_cast< CustomerInfoObject*>(this));
    return TSqlObject::qt_metacast(_clname);
}

int CustomerInfoObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        case 3: *reinterpret_cast< int*>(_v) = getl_id(); break;
        case 4: *reinterpret_cast< QString*>(_v) = getlast_name(); break;
        case 5: *reinterpret_cast< QString*>(_v) = getfirst_name(); break;
        case 6: *reinterpret_cast< QDateTime*>(_v) = getbirthday(); break;
        case 7: *reinterpret_cast< QString*>(_v) = gete_mail_addr(); break;
        case 8: *reinterpret_cast< QString*>(_v) = getphone_num(); break;
        default: break;
        }
        _id -= 9;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setid(*reinterpret_cast< int*>(_v)); break;
        case 1: setcreated_at(*reinterpret_cast< QDateTime*>(_v)); break;
        case 2: setupdated_at(*reinterpret_cast< QDateTime*>(_v)); break;
        case 3: setl_id(*reinterpret_cast< int*>(_v)); break;
        case 4: setlast_name(*reinterpret_cast< QString*>(_v)); break;
        case 5: setfirst_name(*reinterpret_cast< QString*>(_v)); break;
        case 6: setbirthday(*reinterpret_cast< QDateTime*>(_v)); break;
        case 7: sete_mail_addr(*reinterpret_cast< QString*>(_v)); break;
        case 8: setphone_num(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
        _id -= 9;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 9;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
