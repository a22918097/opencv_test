/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[327];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 27), // "on_pushButton_close_clicked"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 24), // "on_actionClose_triggered"
QT_MOC_LITERAL(4, 65, 27), // "on_pushButton_pause_clicked"
QT_MOC_LITERAL(5, 93, 26), // "on_pushButton_Read_clicked"
QT_MOC_LITERAL(6, 120, 26), // "on_pushButton_play_clicked"
QT_MOC_LITERAL(7, 147, 26), // "on_pushButton_save_clicked"
QT_MOC_LITERAL(8, 174, 9), // "svDisplay"
QT_MOC_LITERAL(9, 184, 8), // "cv::Mat*"
QT_MOC_LITERAL(10, 193, 5), // "img_L"
QT_MOC_LITERAL(11, 199, 5), // "img_R"
QT_MOC_LITERAL(12, 205, 4), // "disp"
QT_MOC_LITERAL(13, 210, 11), // "disp_pseudo"
QT_MOC_LITERAL(14, 222, 34), // "on_checkBox_do_calibration_cl..."
QT_MOC_LITERAL(15, 257, 7), // "checked"
QT_MOC_LITERAL(16, 265, 28), // "on_checkBox_do_depth_clicked"
QT_MOC_LITERAL(17, 294, 32) // "on_checkBox_pseudo_color_clicked"

    },
    "MainWindow\0on_pushButton_close_clicked\0"
    "\0on_actionClose_triggered\0"
    "on_pushButton_pause_clicked\0"
    "on_pushButton_Read_clicked\0"
    "on_pushButton_play_clicked\0"
    "on_pushButton_save_clicked\0svDisplay\0"
    "cv::Mat*\0img_L\0img_R\0disp\0disp_pseudo\0"
    "on_checkBox_do_calibration_clicked\0"
    "checked\0on_checkBox_do_depth_clicked\0"
    "on_checkBox_pseudo_color_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    4,   70,    2, 0x08 /* Private */,
      14,    1,   79,    2, 0x08 /* Private */,
      16,    1,   82,    2, 0x08 /* Private */,
      17,    1,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9, 0x80000000 | 9, 0x80000000 | 9,   10,   11,   12,   13,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Bool,   15,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_close_clicked(); break;
        case 1: _t->on_actionClose_triggered(); break;
        case 2: _t->on_pushButton_pause_clicked(); break;
        case 3: _t->on_pushButton_Read_clicked(); break;
        case 4: _t->on_pushButton_play_clicked(); break;
        case 5: _t->on_pushButton_save_clicked(); break;
        case 6: _t->svDisplay((*reinterpret_cast< cv::Mat*(*)>(_a[1])),(*reinterpret_cast< cv::Mat*(*)>(_a[2])),(*reinterpret_cast< cv::Mat*(*)>(_a[3])),(*reinterpret_cast< cv::Mat*(*)>(_a[4]))); break;
        case 7: _t->on_checkBox_do_calibration_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_checkBox_do_depth_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_checkBox_pseudo_color_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
