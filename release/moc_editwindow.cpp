/****************************************************************************
** Meta object code from reading C++ file 'editwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/windows/editwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EditWindow_t {
    QByteArrayData data[14];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditWindow_t qt_meta_stringdata_EditWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "EditWindow"
QT_MOC_LITERAL(1, 11, 12), // "retakeSignal"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "editOver"
QT_MOC_LITERAL(4, 34, 4), // "host"
QT_MOC_LITERAL(5, 39, 8), // "validate"
QT_MOC_LITERAL(6, 48, 6), // "retake"
QT_MOC_LITERAL(7, 55, 4), // "save"
QT_MOC_LITERAL(8, 60, 17), // "copyIntoClipboard"
QT_MOC_LITERAL(9, 78, 16), // "uploadScreenshot"
QT_MOC_LITERAL(10, 95, 14), // "changePenWidth"
QT_MOC_LITERAL(11, 110, 5), // "width"
QT_MOC_LITERAL(12, 116, 14), // "changePenColor"
QT_MOC_LITERAL(13, 131, 17) // "changeDrawingTool"

    },
    "EditWindow\0retakeSignal\0\0editOver\0"
    "host\0validate\0retake\0save\0copyIntoClipboard\0"
    "uploadScreenshot\0changePenWidth\0width\0"
    "changePenColor\0changeDrawingTool"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    1,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   68,    2, 0x0a /* Public */,
       6,    0,   69,    2, 0x0a /* Public */,
       7,    0,   70,    2, 0x0a /* Public */,
       8,    0,   71,    2, 0x0a /* Public */,
       9,    0,   72,    2, 0x0a /* Public */,
      10,    1,   73,    2, 0x0a /* Public */,
      12,    0,   76,    2, 0x0a /* Public */,
      13,    0,   77,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EditWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EditWindow *_t = static_cast<EditWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->retakeSignal(); break;
        case 1: _t->editOver((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->validate(); break;
        case 3: _t->retake(); break;
        case 4: _t->save(); break;
        case 5: _t->copyIntoClipboard(); break;
        case 6: _t->uploadScreenshot(); break;
        case 7: _t->changePenWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->changePenColor(); break;
        case 9: _t->changeDrawingTool(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EditWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EditWindow::retakeSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (EditWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EditWindow::editOver)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject EditWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_EditWindow.data,
      qt_meta_data_EditWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EditWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EditWindow.stringdata0))
        return static_cast<void*>(const_cast< EditWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int EditWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void EditWindow::retakeSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void EditWindow::editOver(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
