/****************************************************************************
** Meta object code from reading C++ file 'pravekshaui.h'
**
** Created: Wed Dec 4 09:03:34 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../pravekshaui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pravekshaui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PravekshaUI[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      47,   12,   12,   12, 0x0a,
      80,   12,   12,   12, 0x0a,
     103,   12,   12,   12, 0x0a,
     133,   12,   12,   12, 0x0a,
     167,  161,   12,   12, 0x0a,
     198,   12,   12,   12, 0x0a,
     229,  219,   12,   12, 0x08,
     254,  251,   12,   12, 0x08,
     278,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PravekshaUI[] = {
    "PravekshaUI\0\0on_btnStartCallibration_clicked()\0"
    "on_btnStopCallibration_clicked()\0"
    "on_btnBrowse_clicked()\0"
    "on_btnSetLoggerPath_clicked()\0"
    "on_btnSetDistance_clicked()\0index\0"
    "onListItemClicked(QModelIndex)\0"
    "on_btnStat_clicked()\0violation\0"
    "updateLogList(String)\0id\0"
    "currentChangedSlot(int)\0updateStat()\0"
};

void PravekshaUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PravekshaUI *_t = static_cast<PravekshaUI *>(_o);
        switch (_id) {
        case 0: _t->on_btnStartCallibration_clicked(); break;
        case 1: _t->on_btnStopCallibration_clicked(); break;
        case 2: _t->on_btnBrowse_clicked(); break;
        case 3: _t->on_btnSetLoggerPath_clicked(); break;
        case 4: _t->on_btnSetDistance_clicked(); break;
        case 5: _t->onListItemClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: _t->on_btnStat_clicked(); break;
        case 7: _t->updateLogList((*reinterpret_cast< String(*)>(_a[1]))); break;
        case 8: _t->currentChangedSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->updateStat(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PravekshaUI::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PravekshaUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_PravekshaUI,
      qt_meta_data_PravekshaUI, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PravekshaUI::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PravekshaUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PravekshaUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PravekshaUI))
        return static_cast<void*>(const_cast< PravekshaUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int PravekshaUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
