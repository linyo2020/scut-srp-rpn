/****************************************************************************
** Meta object code from reading C++ file 'petritabwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../reconfigurablePetri/petritabwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'petritabwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PetriTabWidget_t {
    QByteArrayData data[18];
    char stringdata0[178];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PetriTabWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PetriTabWidget_t qt_meta_stringdata_PetriTabWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PetriTabWidget"
QT_MOC_LITERAL(1, 15, 13), // "canRedoChange"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 7), // "canRedo"
QT_MOC_LITERAL(4, 38, 13), // "canUndoChange"
QT_MOC_LITERAL(5, 52, 7), // "canUndo"
QT_MOC_LITERAL(6, 60, 10), // "netChanged"
QT_MOC_LITERAL(7, 71, 7), // "changed"
QT_MOC_LITERAL(8, 79, 12), // "errorMessage"
QT_MOC_LITERAL(9, 92, 3), // "msg"
QT_MOC_LITERAL(10, 96, 12), // "nodeInserted"
QT_MOC_LITERAL(11, 109, 7), // "itemPos"
QT_MOC_LITERAL(12, 117, 2), // "id"
QT_MOC_LITERAL(13, 120, 13), // "nodesInserted"
QT_MOC_LITERAL(14, 134, 5), // "names"
QT_MOC_LITERAL(15, 140, 17), // "itemDoubleClicked"
QT_MOC_LITERAL(16, 158, 14), // "QGraphicsItem*"
QT_MOC_LITERAL(17, 173, 4) // "item"

    },
    "PetriTabWidget\0canRedoChange\0\0canRedo\0"
    "canUndoChange\0canUndo\0netChanged\0"
    "changed\0errorMessage\0msg\0nodeInserted\0"
    "itemPos\0id\0nodesInserted\0names\0"
    "itemDoubleClicked\0QGraphicsItem*\0item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PetriTabWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,
       6,    1,   55,    2, 0x06 /* Public */,
       8,    1,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    2,   61,    2, 0x0a /* Public */,
      13,    1,   66,    2, 0x0a /* Public */,
      15,    1,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::QString,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::QPointF, QMetaType::QString,   11,   12,
    QMetaType::Void, QMetaType::QStringList,   14,
    QMetaType::Void, 0x80000000 | 16,   17,

       0        // eod
};

void PetriTabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PetriTabWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->canRedoChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->canUndoChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->netChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->errorMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->nodeInserted((*reinterpret_cast< const QPointF(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->nodesInserted((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 6: _t->itemDoubleClicked((*reinterpret_cast< QGraphicsItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGraphicsItem* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PetriTabWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PetriTabWidget::canRedoChange)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PetriTabWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PetriTabWidget::canUndoChange)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PetriTabWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PetriTabWidget::netChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PetriTabWidget::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PetriTabWidget::errorMessage)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PetriTabWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_PetriTabWidget.data,
    qt_meta_data_PetriTabWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PetriTabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PetriTabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PetriTabWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int PetriTabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void PetriTabWidget::canRedoChange(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PetriTabWidget::canUndoChange(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PetriTabWidget::netChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PetriTabWidget::errorMessage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
