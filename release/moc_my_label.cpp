/****************************************************************************
** Meta object code from reading C++ file 'my_label.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Counter2/my_label.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'my_label.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_my_label_t {
    QByteArrayData data[7];
    char stringdata0[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_my_label_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_my_label_t qt_meta_stringdata_my_label = {
    {
QT_MOC_LITERAL(0, 0, 8), // "my_label"
QT_MOC_LITERAL(1, 9, 13), // "Mouse_Pressed"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 9), // "Mouse_Pos"
QT_MOC_LITERAL(4, 34, 10), // "Mouse_left"
QT_MOC_LITERAL(5, 45, 13), // "Mouse_Release"
QT_MOC_LITERAL(6, 59, 10) // "Wheel_Roll"

    },
    "my_label\0Mouse_Pressed\0\0Mouse_Pos\0"
    "Mouse_left\0Mouse_Release\0Wheel_Roll"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_my_label[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,
       5,    0,   42,    2, 0x06 /* Public */,
       6,    0,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void my_label::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<my_label *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Mouse_Pressed(); break;
        case 1: _t->Mouse_Pos(); break;
        case 2: _t->Mouse_left(); break;
        case 3: _t->Mouse_Release(); break;
        case 4: _t->Wheel_Roll(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (my_label::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&my_label::Mouse_Pressed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (my_label::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&my_label::Mouse_Pos)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (my_label::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&my_label::Mouse_left)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (my_label::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&my_label::Mouse_Release)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (my_label::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&my_label::Wheel_Roll)) {
                *result = 4;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject my_label::staticMetaObject = { {
    QMetaObject::SuperData::link<QLabel::staticMetaObject>(),
    qt_meta_stringdata_my_label.data,
    qt_meta_data_my_label,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *my_label::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *my_label::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_my_label.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int my_label::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void my_label::Mouse_Pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void my_label::Mouse_Pos()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void my_label::Mouse_left()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void my_label::Mouse_Release()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void my_label::Wheel_Roll()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
