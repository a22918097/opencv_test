/****************************************************************************
** Meta object code from reading C++ file 'stereo_vision.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../stereo_vision.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stereo_vision.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_stereo_vision_t {
    QByteArrayData data[18];
    char stringdata0[293];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_stereo_vision_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_stereo_vision_t qt_meta_stringdata_stereo_vision = {
    {
QT_MOC_LITERAL(0, 0, 13), // "stereo_vision"
QT_MOC_LITERAL(1, 14, 9), // "updateGUI"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "cv::Mat*"
QT_MOC_LITERAL(4, 34, 5), // "img_L"
QT_MOC_LITERAL(5, 40, 5), // "img_R"
QT_MOC_LITERAL(6, 46, 4), // "disp"
QT_MOC_LITERAL(7, 51, 11), // "disp_pseudo"
QT_MOC_LITERAL(8, 63, 25), // "change_bm_pre_filter_size"
QT_MOC_LITERAL(9, 89, 5), // "value"
QT_MOC_LITERAL(10, 95, 24), // "change_bm_pre_filter_cap"
QT_MOC_LITERAL(11, 120, 25), // "change_bm_sad_window_size"
QT_MOC_LITERAL(12, 146, 18), // "change_bm_min_disp"
QT_MOC_LITERAL(13, 165, 21), // "change_bm_num_of_disp"
QT_MOC_LITERAL(14, 187, 24), // "change_bm_texture_thresh"
QT_MOC_LITERAL(15, 212, 26), // "change_bm_uniqueness_ratio"
QT_MOC_LITERAL(16, 239, 29), // "change_bm_speckle_window_size"
QT_MOC_LITERAL(17, 269, 23) // "change_bm_speckle_range"

    },
    "stereo_vision\0updateGUI\0\0cv::Mat*\0"
    "img_L\0img_R\0disp\0disp_pseudo\0"
    "change_bm_pre_filter_size\0value\0"
    "change_bm_pre_filter_cap\0"
    "change_bm_sad_window_size\0change_bm_min_disp\0"
    "change_bm_num_of_disp\0change_bm_texture_thresh\0"
    "change_bm_uniqueness_ratio\0"
    "change_bm_speckle_window_size\0"
    "change_bm_speckle_range"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_stereo_vision[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   73,    2, 0x08 /* Private */,
      10,    1,   76,    2, 0x08 /* Private */,
      11,    1,   79,    2, 0x08 /* Private */,
      12,    1,   82,    2, 0x08 /* Private */,
      13,    1,   85,    2, 0x08 /* Private */,
      14,    1,   88,    2, 0x08 /* Private */,
      15,    1,   91,    2, 0x08 /* Private */,
      16,    1,   94,    2, 0x08 /* Private */,
      17,    1,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,    4,    5,    6,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void stereo_vision::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        stereo_vision *_t = static_cast<stereo_vision *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateGUI((*reinterpret_cast< cv::Mat*(*)>(_a[1])),(*reinterpret_cast< cv::Mat*(*)>(_a[2])),(*reinterpret_cast< cv::Mat*(*)>(_a[3])),(*reinterpret_cast< cv::Mat*(*)>(_a[4]))); break;
        case 1: _t->change_bm_pre_filter_size((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->change_bm_pre_filter_cap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->change_bm_sad_window_size((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->change_bm_min_disp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->change_bm_num_of_disp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->change_bm_texture_thresh((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->change_bm_uniqueness_ratio((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->change_bm_speckle_window_size((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->change_bm_speckle_range((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (stereo_vision::*_t)(cv::Mat * , cv::Mat * , cv::Mat * , cv::Mat * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&stereo_vision::updateGUI)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject stereo_vision::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_stereo_vision.data,
      qt_meta_data_stereo_vision,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *stereo_vision::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stereo_vision::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_stereo_vision.stringdata0))
        return static_cast<void*>(const_cast< stereo_vision*>(this));
    if (!strcmp(_clname, "TopView"))
        return static_cast< TopView*>(const_cast< stereo_vision*>(this));
    if (!strcmp(_clname, "SensorBase"))
        return static_cast< SensorBase*>(const_cast< stereo_vision*>(this));
    return QObject::qt_metacast(_clname);
}

int stereo_vision::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void stereo_vision::updateGUI(cv::Mat * _t1, cv::Mat * _t2, cv::Mat * _t3, cv::Mat * _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
