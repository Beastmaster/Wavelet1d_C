/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../window/MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   11,   11,   11, 0x0a,
      46,   11,   11,   11, 0x0a,
      58,   11,   11,   11, 0x0a,
      71,   11,   11,   11, 0x0a,
      83,   11,   11,   11, 0x0a,
     105,   11,   11,   11, 0x0a,
     123,   11,   11,   11, 0x0a,
     141,   11,   11,   11, 0x0a,
     157,   11,   11,   11, 0x0a,
     175,   11,   11,   11, 0x0a,
     191,   11,   11,   11, 0x0a,
     206,   11,   11,   11, 0x0a,
     221,   11,   11,   11, 0x0a,
     241,   11,   11,   11, 0x0a,
     258,   11,   11,   11, 0x0a,
     283,   11,   11,   11, 0x0a,
     303,   11,   11,   11, 0x0a,
     321,   11,   11,   11, 0x0a,
     341,   11,   11,   11, 0x0a,
     365,   11,   11,   11, 0x0a,
     397,  389,   11,   11, 0x0a,
     419,   11,   11,   11, 0x0a,
     436,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0get_data_Done(double)\0"
    "find_Port()\0open_Port()\0close_Port()\0"
    "send_Data()\0sel_portName(QString)\0"
    "set_BaudRate(int)\0set_dataBits(int)\0"
    "set_Parity(int)\0set_stopBits(int)\0"
    "set_Filter(int)\0set_Level(int)\0"
    "receive_Data()\0info_Panel_Scroll()\0"
    "pass_Dot(double)\0get_refresh_Timeout(int)\0"
    "check_port_Status()\0test_timer_func()\0"
    "change_X_Scope(int)\0change_Y_pos_Scope(int)\0"
    "change_Y_neg_Scope(int)\0checked\0"
    "check_save_Data(bool)\0save_Dot(double)\0"
    "snip_Screen()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->get_data_Done((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->find_Port(); break;
        case 2: _t->open_Port(); break;
        case 3: _t->close_Port(); break;
        case 4: _t->send_Data(); break;
        case 5: _t->sel_portName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->set_BaudRate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->set_dataBits((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->set_Parity((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->set_stopBits((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->set_Filter((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->set_Level((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->receive_Data(); break;
        case 13: _t->info_Panel_Scroll(); break;
        case 14: _t->pass_Dot((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->get_refresh_Timeout((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->check_port_Status(); break;
        case 17: _t->test_timer_func(); break;
        case 18: _t->change_X_Scope((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->change_Y_pos_Scope((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->change_Y_neg_Scope((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->check_save_Data((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->save_Dot((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 23: _t->snip_Screen(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::get_data_Done(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_QwtPlotView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QwtPlotView[] = {
    "QwtPlotView\0\0run()\0"
};

void QwtPlotView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QwtPlotView *_t = static_cast<QwtPlotView *>(_o);
        switch (_id) {
        case 0: _t->run(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QwtPlotView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QwtPlotView::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_QwtPlotView,
      qt_meta_data_QwtPlotView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QwtPlotView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QwtPlotView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QwtPlotView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QwtPlotView))
        return static_cast<void*>(const_cast< QwtPlotView*>(this));
    return QThread::qt_metacast(_clname);
}

int QwtPlotView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
