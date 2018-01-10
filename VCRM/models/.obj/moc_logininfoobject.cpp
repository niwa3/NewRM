/****************************************************************************
** Meta object code from reading C++ file 'logininfoobject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sqlobjects/logininfoobject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logininfoobject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LoginInfoObject_t {
    QByteArrayData data[8];
    char stringdata[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LoginInfoObject_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LoginInfoObject_t qt_meta_stringdata_LoginInfoObject = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 2),
QT_MOC_LITERAL(2, 19, 10),
QT_MOC_LITERAL(3, 30, 10),
QT_MOC_LITERAL(4, 41, 5),
QT_MOC_LITERAL(5, 47, 6),
QT_MOC_LITERAL(6, 54, 4),
QT_MOC_LITERAL(7, 59, 9)
    },
    "LoginInfoObject\0id\0created_at\0updated_at\0"
    "login\0passwd\0salt\0user_type"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoginInfoObject[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       7,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::Int, 0x00095003,
       2, QMetaType::QDateTime, 0x00095003,
       3, QMetaType::QDateTime, 0x00095003,
       4, QMetaType::QString, 0x00095003,
       5, QMetaType::QString, 0x00095003,
       6, QMetaType::QString, 0x00095003,
       7, QMetaType::Int, 0x00095003,

       0        // eod
};

void LoginInfoObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject LoginInfoObject::staticMetaObject = {
    { &TSqlObject::staticMetaObject, qt_meta_stringdata_LoginInfoObject.data,
      qt_meta_data_LoginInfoObject,  qt_static_metacall, 0, 0}
};


const QMetaObject *LoginInfoObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoginInfoObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoginInfoObject.stringdata))
        return static_cast<void*>(const_cast< LoginInfoObject*>(this));
    if (!strcmp(_clname, "QSharedData"))
        return static_cast< QSharedData*>(const_cast< LoginInfoObject*>(this));
    return TSqlObject::qt_metacast(_clname);
}

int LoginInfoObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
        case 3: *reinterpret_cast< QString*>(_v) = getlogin(); break;
        case 4: *reinterpret_cast< QString*>(_v) = getpasswd(); break;
        case 5: *reinterpret_cast< QString*>(_v) = getsalt(); break;
        case 6: *reinterpret_cast< int*>(_v) = getuser_type(); break;
        default: break;
        }
        _id -= 7;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setid(*reinterpret_cast< int*>(_v)); break;
        case 1: setcreated_at(*reinterpret_cast< QDateTime*>(_v)); break;
        case 2: setupdated_at(*reinterpret_cast< QDateTime*>(_v)); break;
        case 3: setlogin(*reinterpret_cast< QString*>(_v)); break;
        case 4: setpasswd(*reinterpret_cast< QString*>(_v)); break;
        case 5: setsalt(*reinterpret_cast< QString*>(_v)); break;
        case 6: setuser_type(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
        _id -= 7;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
