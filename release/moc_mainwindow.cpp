/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/windows/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata0[343];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "restore"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 12), // "openSettings"
QT_MOC_LITERAL(4, 33, 9), // "openAbout"
QT_MOC_LITERAL(5, 43, 18), // "activationTrayIcon"
QT_MOC_LITERAL(6, 62, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(7, 96, 6), // "reason"
QT_MOC_LITERAL(8, 103, 14), // "takeScreenshot"
QT_MOC_LITERAL(9, 118, 27), // "openEditWindowNewScreenshot"
QT_MOC_LITERAL(10, 146, 11), // "Screenshot*"
QT_MOC_LITERAL(11, 158, 10), // "screenshot"
QT_MOC_LITERAL(12, 169, 21), // "saveMergedScreenshots"
QT_MOC_LITERAL(13, 191, 34), // "copyIntoClipboardMergedScreen..."
QT_MOC_LITERAL(14, 226, 23), // "uploadMergedScreenshots"
QT_MOC_LITERAL(15, 250, 27), // "openEditWindowOldScreenshot"
QT_MOC_LITERAL(16, 278, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(17, 295, 17), // "screenshotClicked"
QT_MOC_LITERAL(18, 313, 7), // "upImage"
QT_MOC_LITERAL(19, 321, 9), // "downImage"
QT_MOC_LITERAL(20, 331, 11) // "deleteImage"

    },
    "MainWindow\0restore\0\0openSettings\0"
    "openAbout\0activationTrayIcon\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason\0takeScreenshot\0openEditWindowNewScreenshot\0"
    "Screenshot*\0screenshot\0saveMergedScreenshots\0"
    "copyIntoClipboardMergedScreenshots\0"
    "uploadMergedScreenshots\0"
    "openEditWindowOldScreenshot\0"
    "QListWidgetItem*\0screenshotClicked\0"
    "upImage\0downImage\0deleteImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a /* Public */,
       3,    0,   85,    2, 0x0a /* Public */,
       4,    0,   86,    2, 0x0a /* Public */,
       5,    1,   87,    2, 0x0a /* Public */,
       8,    0,   90,    2, 0x0a /* Public */,
       9,    1,   91,    2, 0x0a /* Public */,
      12,    0,   94,    2, 0x0a /* Public */,
      13,    0,   95,    2, 0x0a /* Public */,
      14,    0,   96,    2, 0x0a /* Public */,
      15,    0,   97,    2, 0x0a /* Public */,
      15,    1,   98,    2, 0x0a /* Public */,
      18,    0,  101,    2, 0x0a /* Public */,
      19,    0,  102,    2, 0x0a /* Public */,
      20,    0,  103,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->restore(); break;
        case 1: _t->openSettings(); break;
        case 2: _t->openAbout(); break;
        case 3: _t->activationTrayIcon((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 4: _t->takeScreenshot(); break;
        case 5: _t->openEditWindowNewScreenshot((*reinterpret_cast< Screenshot*(*)>(_a[1]))); break;
        case 6: _t->saveMergedScreenshots(); break;
        case 7: _t->copyIntoClipboardMergedScreenshots(); break;
        case 8: _t->uploadMergedScreenshots(); break;
        case 9: _t->openEditWindowOldScreenshot(); break;
        case 10: _t->openEditWindowOldScreenshot((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 11: _t->upImage(); break;
        case 12: _t->downImage(); break;
        case 13: _t->deleteImage(); break;
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
