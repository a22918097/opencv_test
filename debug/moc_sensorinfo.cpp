/****************************************************************************
** Meta object code from reading C++ file 'sensorinfo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sensorinfo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sensorinfo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SensorInfo_t {
    QByteArrayData data[9];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SensorInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SensorInfo_t qt_meta_stringdata_SensorInfo = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SensorInfo"
QT_MOC_LITERAL(1, 11, 9), // "updateGUI"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "cv::Mat*"
QT_MOC_LITERAL(4, 31, 13), // "fused_topview"
QT_MOC_LITERAL(5, 45, 20), // "img_detected_display"
QT_MOC_LITERAL(6, 66, 10), // "guiDisplay"
QT_MOC_LITERAL(7, 77, 4), // "type"
QT_MOC_LITERAL(8, 82, 5) // "fg_on"

    },
    "SensorInfo\0updateGUI\0\0cv::Mat*\0"
    "fused_topview\0img_detected_display\0"
    "guiDisplay\0type\0fg_on"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SensorInfo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,
       6,    2,   29,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    7,    8,

       0        // eod
};

void SensorInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SensorInfo *_t = static_cast<SensorInfo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateGUI((*reinterpret_cast< cv::Mat*(*)>(_a[1])),(*reinterpret_cast< cv::Mat*(*)>(_a[2]))); break;
        case 1: _t->guiDisplay((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SensorInfo::*_t)(cv::Mat * , cv::Mat * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SensorInfo::updateGUI)) {
                *result = 0;
            }
        }
        {
            typedef void (SensorInfo::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SensorInfo::guiDisplay)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject SensorInfo::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SensorInfo.data,
      qt_meta_data_SensorInfo,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SensorInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SensorInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SensorInfo.stringdata0))
        return static_cast<void*>(const_cast< SensorInfo*>(this));
    return QObject::qt_metacast(_clname);
}

int SensorInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SensorInfo::updateGUI(cv::Mat * _t1, cv::Mat * _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SensorInfo::guiDisplay(int _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
