/****************************************************************************
** Meta object code from reading C++ file 'printhtml.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../PrintHtml-JSON/printhtml.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'printhtml.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PrintHtml[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      22,   10,   10,   10, 0x0a,
      28,   10,   10,   10, 0x0a,
      48,   45,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PrintHtml[] = {
    "PrintHtml\0\0finished()\0run()\0"
    "aboutToQuitApp()\0ok\0htmlLoaded(bool)\0"
};

void PrintHtml::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PrintHtml *_t = static_cast<PrintHtml *>(_o);
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->run(); break;
        case 2: _t->aboutToQuitApp(); break;
        case 3: _t->htmlLoaded((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PrintHtml::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PrintHtml::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PrintHtml,
      qt_meta_data_PrintHtml, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PrintHtml::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PrintHtml::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PrintHtml::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PrintHtml))
        return static_cast<void*>(const_cast< PrintHtml*>(this));
    return QObject::qt_metacast(_clname);
}

int PrintHtml::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void PrintHtml::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
