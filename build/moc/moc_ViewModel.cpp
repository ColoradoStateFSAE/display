/****************************************************************************
** Meta object code from reading C++ file 'ViewModel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.14)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/ViewModel/ViewModel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ViewModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.14. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ViewModel_t {
    QByteArrayData data[15];
    char stringdata0[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ViewModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ViewModel_t qt_meta_stringdata_ViewModel = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ViewModel"
QT_MOC_LITERAL(1, 10, 11), // "gearChanged"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 5), // "value"
QT_MOC_LITERAL(4, 29, 10), // "rpmChanged"
QT_MOC_LITERAL(5, 40, 14), // "batteryChanged"
QT_MOC_LITERAL(6, 55, 14), // "coolantChanged"
QT_MOC_LITERAL(7, 70, 10), // "tpsChanged"
QT_MOC_LITERAL(8, 81, 10), // "afrChanged"
QT_MOC_LITERAL(9, 92, 13), // "clutchChanged"
QT_MOC_LITERAL(10, 106, 10), // "oilChanged"
QT_MOC_LITERAL(11, 117, 13), // "shiftReceived"
QT_MOC_LITERAL(12, 131, 10), // "ecuOffline"
QT_MOC_LITERAL(13, 142, 5), // "state"
QT_MOC_LITERAL(14, 148, 21) // "shiftingSystemOffline"

    },
    "ViewModel\0gearChanged\0\0value\0rpmChanged\0"
    "batteryChanged\0coolantChanged\0tpsChanged\0"
    "afrChanged\0clutchChanged\0oilChanged\0"
    "shiftReceived\0ecuOffline\0state\0"
    "shiftingSystemOffline"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ViewModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,
       5,    1,   75,    2, 0x06 /* Public */,
       6,    1,   78,    2, 0x06 /* Public */,
       7,    1,   81,    2, 0x06 /* Public */,
       8,    1,   84,    2, 0x06 /* Public */,
       9,    1,   87,    2, 0x06 /* Public */,
      10,    1,   90,    2, 0x06 /* Public */,
      11,    0,   93,    2, 0x06 /* Public */,
      12,    1,   94,    2, 0x06 /* Public */,
      14,    1,   97,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::Bool,   13,

       0        // eod
};

void ViewModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ViewModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->gearChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->rpmChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->batteryChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->coolantChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->tpsChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->afrChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->clutchChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->oilChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->shiftReceived(); break;
        case 9: _t->ecuOffline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->shiftingSystemOffline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ViewModel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewModel::gearChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ViewModel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewModel::rpmChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ViewModel::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewModel::batteryChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ViewModel::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewModel::coolantChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ViewModel::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewModel::tpsChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ViewModel::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewModel::afrChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ViewModel::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewModel::clutchChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ViewModel::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewModel::oilChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ViewModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewModel::shiftReceived)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (ViewModel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewModel::ecuOffline)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (ViewModel::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewModel::shiftingSystemOffline)) {
                *result = 10;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ViewModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ViewModel.data,
    qt_meta_data_ViewModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ViewModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ViewModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ViewModel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ViewModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ViewModel::gearChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ViewModel::rpmChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ViewModel::batteryChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ViewModel::coolantChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ViewModel::tpsChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ViewModel::afrChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ViewModel::clutchChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ViewModel::oilChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ViewModel::shiftReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void ViewModel::ecuOffline(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ViewModel::shiftingSystemOffline(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
