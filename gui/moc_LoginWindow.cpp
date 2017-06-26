/****************************************************************************
** Meta object code from reading C++ file 'LoginWindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "LoginWindow.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LoginWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LoginWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      29,   12,   12,   12, 0x05,
      45,   12,   12,   12, 0x05,
      61,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      77,   12,   12,   12, 0x0a,
      90,   12,   12,   12, 0x0a,
     110,   12,   12,   12, 0x0a,
     133,   12,   12,   12, 0x0a,
     148,   12,   12,   12, 0x0a,
     162,   12,   12,   12, 0x0a,
     176,   12,   12,   12, 0x0a,
     190,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LoginWindow[] = {
    "LoginWindow\0\0showLogSignal()\0"
    "hideLogSignal()\0showRegSignal()\0"
    "hideRegSignal()\0openRegWin()\0"
    "checkLogin(QString)\0checkPassword(QString)\0"
    "sendLoginReq()\0showLogSlot()\0hideLogSlot()\0"
    "showRegSlot()\0hideRegSlot()\0"
};

void LoginWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LoginWindow *_t = static_cast<LoginWindow *>(_o);
        switch (_id) {
        case 0: _t->showLogSignal(); break;
        case 1: _t->hideLogSignal(); break;
        case 2: _t->showRegSignal(); break;
        case 3: _t->hideRegSignal(); break;
        case 4: _t->openRegWin(); break;
        case 5: _t->checkLogin((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->checkPassword((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->sendLoginReq(); break;
        case 8: _t->showLogSlot(); break;
        case 9: _t->hideLogSlot(); break;
        case 10: _t->showRegSlot(); break;
        case 11: _t->hideRegSlot(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LoginWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LoginWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LoginWindow,
      qt_meta_data_LoginWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LoginWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LoginWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LoginWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LoginWindow))
        return static_cast<void*>(const_cast< LoginWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int LoginWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void LoginWindow::showLogSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void LoginWindow::hideLogSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void LoginWindow::showRegSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void LoginWindow::hideRegSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
