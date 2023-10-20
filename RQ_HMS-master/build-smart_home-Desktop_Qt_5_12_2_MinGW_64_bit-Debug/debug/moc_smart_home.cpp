/****************************************************************************
** Meta object code from reading C++ file 'smart_home.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../code/QT_client/smart_home.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'smart_home.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_smart_home_t {
    QByteArrayData data[9];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_smart_home_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_smart_home_t qt_meta_stringdata_smart_home = {
    {
QT_MOC_LITERAL(0, 0, 10), // "smart_home"
QT_MOC_LITERAL(1, 11, 7), // "soltLog"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 13), // "soltConnected"
QT_MOC_LITERAL(4, 34, 8), // "soltRecv"
QT_MOC_LITERAL(5, 43, 9), // "soltClose"
QT_MOC_LITERAL(6, 53, 13), // "clickedAtHome"
QT_MOC_LITERAL(7, 67, 16), // "clickedLeaveHome"
QT_MOC_LITERAL(8, 84, 9) // "checkedBT"

    },
    "smart_home\0soltLog\0\0soltConnected\0"
    "soltRecv\0soltClose\0clickedAtHome\0"
    "clickedLeaveHome\0checkedBT"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_smart_home[] = {

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
       1,    0,   49,    2, 0x09 /* Protected */,
       3,    0,   50,    2, 0x09 /* Protected */,
       4,    0,   51,    2, 0x09 /* Protected */,
       5,    0,   52,    2, 0x09 /* Protected */,
       6,    0,   53,    2, 0x09 /* Protected */,
       7,    0,   54,    2, 0x09 /* Protected */,
       8,    0,   55,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void smart_home::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<smart_home *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->soltLog(); break;
        case 1: _t->soltConnected(); break;
        case 2: _t->soltRecv(); break;
        case 3: _t->soltClose(); break;
        case 4: _t->clickedAtHome(); break;
        case 5: _t->clickedLeaveHome(); break;
        case 6: _t->checkedBT(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject smart_home::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_smart_home.data,
    qt_meta_data_smart_home,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *smart_home::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *smart_home::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_smart_home.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int smart_home::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
