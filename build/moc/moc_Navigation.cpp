/****************************************************************************
** Meta object code from reading C++ file 'Navigation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.14)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/Navigation/Navigation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Navigation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.14. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Navigation_t {
    QByteArrayData data[20];
    char stringdata0[177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Navigation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Navigation_t qt_meta_stringdata_Navigation = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Navigation"
QT_MOC_LITERAL(1, 11, 18), // "changeTaskSwitcher"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 13), // "cursorChanged"
QT_MOC_LITERAL(4, 45, 12), // "shiftChanged"
QT_MOC_LITERAL(5, 58, 13), // "clutchChanged"
QT_MOC_LITERAL(6, 72, 5), // "State"
QT_MOC_LITERAL(7, 78, 4), // "EXIT"
QT_MOC_LITERAL(8, 83, 5), // "ABOUT"
QT_MOC_LITERAL(9, 89, 5), // "SHIFT"
QT_MOC_LITERAL(10, 95, 6), // "CLUTCH"
QT_MOC_LITERAL(11, 102, 8), // "UP_DELAY"
QT_MOC_LITERAL(12, 111, 10), // "DOWN_DELAY"
QT_MOC_LITERAL(13, 122, 6), // "OUTPUT"
QT_MOC_LITERAL(14, 129, 7), // "TIMEOUT"
QT_MOC_LITERAL(15, 137, 5), // "START"
QT_MOC_LITERAL(16, 143, 3), // "END"
QT_MOC_LITERAL(17, 147, 8), // "FRICTION"
QT_MOC_LITERAL(18, 156, 8), // "POSITION"
QT_MOC_LITERAL(19, 165, 11) // "AUTO_LAUNCH"

    },
    "Navigation\0changeTaskSwitcher\0\0"
    "cursorChanged\0shiftChanged\0clutchChanged\0"
    "State\0EXIT\0ABOUT\0SHIFT\0CLUTCH\0UP_DELAY\0"
    "DOWN_DELAY\0OUTPUT\0TIMEOUT\0START\0END\0"
    "FRICTION\0POSITION\0AUTO_LAUNCH"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Navigation[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       1,   62, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       3,    2,   37,    2, 0x06 /* Public */,
       4,    4,   42,    2, 0x06 /* Public */,
       5,    5,   51,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,    2,

 // enums: name, alias, flags, count, data
       6,    6, 0x0,   13,   67,

 // enum data: key, value
       7, uint(Navigation::EXIT),
       8, uint(Navigation::ABOUT),
       9, uint(Navigation::SHIFT),
      10, uint(Navigation::CLUTCH),
      11, uint(Navigation::UP_DELAY),
      12, uint(Navigation::DOWN_DELAY),
      13, uint(Navigation::OUTPUT),
      14, uint(Navigation::TIMEOUT),
      15, uint(Navigation::START),
      16, uint(Navigation::END),
      17, uint(Navigation::FRICTION),
      18, uint(Navigation::POSITION),
      19, uint(Navigation::AUTO_LAUNCH),

       0        // eod
};

void Navigation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Navigation *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->changeTaskSwitcher((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->cursorChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->shiftChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 3: _t->clutchChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Navigation::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Navigation::changeTaskSwitcher)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Navigation::*)(int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Navigation::cursorChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Navigation::*)(int , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Navigation::shiftChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Navigation::*)(int , int , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Navigation::clutchChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Navigation::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Navigation.data,
    qt_meta_data_Navigation,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Navigation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Navigation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Navigation.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Navigation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Navigation::changeTaskSwitcher(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Navigation::cursorChanged(int _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Navigation::shiftChanged(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Navigation::clutchChanged(int _t1, int _t2, int _t3, int _t4, int _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
