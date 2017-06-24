/****************************************************************************
** Meta object code from reading C++ file 'RegistrationWindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "RegistrationWindow.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RegistrationWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RegistrationWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      40,   19,   19,   19, 0x0a,
      59,   19,   19,   19, 0x0a,
      81,   19,   19,   19, 0x0a,
     104,   19,   19,   19, 0x0a,
     128,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RegistrationWindow[] = {
    "RegistrationWindow\0\0checkLogin(QString)\0"
    "checkName(QString)\0checkSurname(QString)\0"
    "checkPassword(QString)\0checkPasswords(QString)\0"
    "sendRegistrationReq()\0"
};

void RegistrationWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RegistrationWindow *_t = static_cast<RegistrationWindow *>(_o);
        switch (_id) {
        case 0: _t->checkLogin((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->checkName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->checkSurname((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->checkPassword((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->checkPasswords((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->sendRegistrationReq(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RegistrationWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RegistrationWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RegistrationWindow,
      qt_meta_data_RegistrationWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RegistrationWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RegistrationWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RegistrationWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RegistrationWindow))
        return static_cast<void*>(const_cast< RegistrationWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int RegistrationWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
