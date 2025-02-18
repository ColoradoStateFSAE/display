/****************************************************************************
** Meta object code from reading C++ file 'NeoPixel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.14)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/NeoPixel/NeoPixel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NeoPixel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.14. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NeoPixel_t {
    QByteArrayData data[10];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NeoPixel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NeoPixel_t qt_meta_stringdata_NeoPixel = {
    {
QT_MOC_LITERAL(0, 0, 8), // "NeoPixel"
QT_MOC_LITERAL(1, 9, 5), // "start"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 7), // "warning"
QT_MOC_LITERAL(4, 24, 8), // "critical"
QT_MOC_LITERAL(5, 33, 11), // "rpmReceived"
QT_MOC_LITERAL(6, 45, 5), // "value"
QT_MOC_LITERAL(7, 51, 15), // "batteryReceived"
QT_MOC_LITERAL(8, 67, 15), // "coolantReceived"
QT_MOC_LITERAL(9, 83, 13) // "shiftReceived"

    },
    "NeoPixel\0start\0\0warning\0critical\0"
    "rpmReceived\0value\0batteryReceived\0"
    "coolantReceived\0shiftReceived"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NeoPixel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    1,   52,    2, 0x0a /* Public */,
       7,    1,   55,    2, 0x0a /* Public */,
       8,    1,   58,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Float,    6,
    QMetaType::Void, QMetaType::Float,    6,
    QMetaType::Void,

       0        // eod
};

void NeoPixel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NeoPixel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->start(); break;
        case 1: { bool _r = _t->warning();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { bool _r = _t->critical();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->rpmReceived((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->batteryReceived((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->coolantReceived((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->shiftReceived(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NeoPixel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_NeoPixel.data,
    qt_meta_data_NeoPixel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NeoPixel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NeoPixel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NeoPixel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NeoPixel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
