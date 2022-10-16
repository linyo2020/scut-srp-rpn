/****************************************************************************
** Meta object code from reading C++ file 'undostack.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../reconfigurablePetri/undostack.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'undostack.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UndoStack_t {
    QByteArrayData data[19];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UndoStack_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UndoStack_t qt_meta_stringdata_UndoStack = {
    {
QT_MOC_LITERAL(0, 0, 9), // "UndoStack"
QT_MOC_LITERAL(1, 10, 11), // "arcInserted"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 14), // "QGraphicsItem*"
QT_MOC_LITERAL(4, 38, 5), // "item1"
QT_MOC_LITERAL(5, 44, 5), // "item2"
QT_MOC_LITERAL(6, 50, 12), // "QPainterPath"
QT_MOC_LITERAL(7, 63, 8), // "arc_path"
QT_MOC_LITERAL(8, 72, 2), // "id"
QT_MOC_LITERAL(9, 75, 9), // "PTNscene*"
QT_MOC_LITERAL(10, 85, 5), // "scene"
QT_MOC_LITERAL(11, 91, 9), // "ArcWeight"
QT_MOC_LITERAL(12, 101, 9), // "itemMoved"
QT_MOC_LITERAL(13, 111, 9), // "movedItem"
QT_MOC_LITERAL(14, 121, 11), // "oldPosition"
QT_MOC_LITERAL(15, 133, 11), // "nodeRemoved"
QT_MOC_LITERAL(16, 145, 4), // "item"
QT_MOC_LITERAL(17, 150, 10), // "arcRemoved"
QT_MOC_LITERAL(18, 161, 10) // "arcClicked"

    },
    "UndoStack\0arcInserted\0\0QGraphicsItem*\0"
    "item1\0item2\0QPainterPath\0arc_path\0id\0"
    "PTNscene*\0scene\0ArcWeight\0itemMoved\0"
    "movedItem\0oldPosition\0nodeRemoved\0"
    "item\0arcRemoved\0arcClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UndoStack[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    6,   39,    2, 0x0a /* Public */,
      12,    2,   52,    2, 0x0a /* Public */,
      15,    2,   57,    2, 0x0a /* Public */,
      17,    2,   62,    2, 0x0a /* Public */,
      18,    2,   67,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 6, QMetaType::QString, 0x80000000 | 9, QMetaType::Int,    4,    5,    7,    8,   10,   11,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QPointF,   13,   14,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 9,   16,   10,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 9,   16,   10,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 9,   16,   10,

       0        // eod
};

void UndoStack::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UndoStack *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->arcInserted((*reinterpret_cast< QGraphicsItem*(*)>(_a[1])),(*reinterpret_cast< QGraphicsItem*(*)>(_a[2])),(*reinterpret_cast< const QPainterPath(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< PTNscene*(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 1: _t->itemMoved((*reinterpret_cast< QGraphicsItem*(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 2: _t->nodeRemoved((*reinterpret_cast< QGraphicsItem*(*)>(_a[1])),(*reinterpret_cast< PTNscene*(*)>(_a[2]))); break;
        case 3: _t->arcRemoved((*reinterpret_cast< QGraphicsItem*(*)>(_a[1])),(*reinterpret_cast< PTNscene*(*)>(_a[2]))); break;
        case 4: _t->arcClicked((*reinterpret_cast< QGraphicsItem*(*)>(_a[1])),(*reinterpret_cast< PTNscene*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 4:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PTNscene* >(); break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGraphicsItem* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGraphicsItem* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PTNscene* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGraphicsItem* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PTNscene* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGraphicsItem* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PTNscene* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGraphicsItem* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UndoStack::staticMetaObject = { {
    &QUndoStack::staticMetaObject,
    qt_meta_stringdata_UndoStack.data,
    qt_meta_data_UndoStack,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UndoStack::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UndoStack::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UndoStack.stringdata0))
        return static_cast<void*>(this);
    return QUndoStack::qt_metacast(_clname);
}

int UndoStack::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QUndoStack::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
