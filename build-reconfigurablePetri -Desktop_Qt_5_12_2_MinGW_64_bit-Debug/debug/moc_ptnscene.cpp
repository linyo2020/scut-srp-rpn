/****************************************************************************
** Meta object code from reading C++ file 'ptnscene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../reconfigurablePetri/ptnscene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ptnscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PTNscene_t {
    QByteArrayData data[24];
    char stringdata0[215];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PTNscene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PTNscene_t qt_meta_stringdata_PTNscene = {
    {
QT_MOC_LITERAL(0, 0, 8), // "PTNscene"
QT_MOC_LITERAL(1, 9, 12), // "nodeInserted"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 7), // "itemPos"
QT_MOC_LITERAL(4, 31, 2), // "id"
QT_MOC_LITERAL(5, 34, 11), // "arcInserted"
QT_MOC_LITERAL(6, 46, 14), // "QGraphicsItem*"
QT_MOC_LITERAL(7, 61, 6), // "source"
QT_MOC_LITERAL(8, 68, 6), // "target"
QT_MOC_LITERAL(9, 75, 12), // "QPainterPath"
QT_MOC_LITERAL(10, 88, 8), // "arc_path"
QT_MOC_LITERAL(11, 97, 9), // "PTNscene*"
QT_MOC_LITERAL(12, 107, 5), // "scene"
QT_MOC_LITERAL(13, 113, 1), // "w"
QT_MOC_LITERAL(14, 115, 1), // "e"
QT_MOC_LITERAL(15, 117, 9), // "itemMoved"
QT_MOC_LITERAL(16, 127, 9), // "movedItem"
QT_MOC_LITERAL(17, 137, 11), // "oldPosition"
QT_MOC_LITERAL(18, 149, 11), // "nodeRemoved"
QT_MOC_LITERAL(19, 161, 4), // "item"
QT_MOC_LITERAL(20, 166, 10), // "arcRemoved"
QT_MOC_LITERAL(21, 177, 13), // "nodesInserted"
QT_MOC_LITERAL(22, 191, 5), // "names"
QT_MOC_LITERAL(23, 197, 17) // "itemDoubleClicked"

    },
    "PTNscene\0nodeInserted\0\0itemPos\0id\0"
    "arcInserted\0QGraphicsItem*\0source\0"
    "target\0QPainterPath\0arc_path\0PTNscene*\0"
    "scene\0w\0e\0itemMoved\0movedItem\0oldPosition\0"
    "nodeRemoved\0item\0arcRemoved\0nodesInserted\0"
    "names\0itemDoubleClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PTNscene[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       5,    7,   64,    2, 0x06 /* Public */,
       5,    6,   79,    2, 0x26 /* Public | MethodCloned */,
       5,    5,   92,    2, 0x26 /* Public | MethodCloned */,
      15,    2,  103,    2, 0x06 /* Public */,
      18,    2,  108,    2, 0x06 /* Public */,
      20,    2,  113,    2, 0x06 /* Public */,
      21,    1,  118,    2, 0x06 /* Public */,
      23,    1,  121,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPointF, QMetaType::QString,    3,    4,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6, 0x80000000 | 9, QMetaType::QString, 0x80000000 | 11, QMetaType::Int, QMetaType::QString,    7,    8,   10,    4,   12,   13,   14,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6, 0x80000000 | 9, QMetaType::QString, 0x80000000 | 11, QMetaType::Int,    7,    8,   10,    4,   12,   13,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6, 0x80000000 | 9, QMetaType::QString, 0x80000000 | 11,    7,    8,   10,    4,   12,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QPointF,   16,   17,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 11,   19,   12,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 11,   19,   12,
    QMetaType::Void, QMetaType::QStringList,   22,
    QMetaType::Void, 0x80000000 | 6,   19,

       0        // eod
};

void PTNscene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PTNscene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nodeInserted((*reinterpret_cast< const QPointF(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->arcInserted((*reinterpret_cast< QGraphicsItem*(*)>(_a[1])),(*reinterpret_cast< QGraphicsItem*(*)>(_a[2])),(*reinterpret_cast< const QPainterPath(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< PTNscene*(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7]))); break;
        case 2: _t->arcInserted((*reinterpret_cast< QGraphicsItem*(*)>(_a[1])),(*reinterpret_cast< QGraphicsItem*(*)>(_a[2])),(*reinterpret_cast< const QPainterPath(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< PTNscene*(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 3: _t->arcInserted((*reinterpret_cast< QGraphicsItem*(*)>(_a[1])),(*reinterpret_cast< QGraphicsItem*(*)>(_a[2])),(*reinterpret_cast< const QPainterPath(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< PTNscene*(*)>(_a[5]))); break;
        case 4: _t->itemMoved((*reinterpret_cast< QGraphicsItem*(*)>(_a[1])),(*reinterpret_cast< const QPointF(*)>(_a[2]))); break;
        case 5: _t->nodeRemoved((*reinterpret_cast< QGraphicsItem*(*)>(_a[1])),(*reinterpret_cast< PTNscene*(*)>(_a[2]))); break;
        case 6: _t->arcRemoved((*reinterpret_cast< QGraphicsItem*(*)>(_a[1])),(*reinterpret_cast< PTNscene*(*)>(_a[2]))); break;
        case 7: _t->nodesInserted((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 8: _t->itemDoubleClicked((*reinterpret_cast< QGraphicsItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 4:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PTNscene* >(); break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGraphicsItem* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 4:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PTNscene* >(); break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGraphicsItem* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 4:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PTNscene* >(); break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGraphicsItem* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGraphicsItem* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PTNscene* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGraphicsItem* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PTNscene* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QGraphicsItem* >(); break;
            }
            break;
        case 8:
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
            using _t = void (PTNscene::*)(const QPointF & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PTNscene::nodeInserted)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PTNscene::*)(QGraphicsItem * , QGraphicsItem * , const QPainterPath & , const QString & , PTNscene * , int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PTNscene::arcInserted)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PTNscene::*)(QGraphicsItem * , const QPointF & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PTNscene::itemMoved)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PTNscene::*)(QGraphicsItem * , PTNscene * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PTNscene::nodeRemoved)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PTNscene::*)(QGraphicsItem * , PTNscene * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PTNscene::arcRemoved)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (PTNscene::*)(const QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PTNscene::nodesInserted)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (PTNscene::*)(QGraphicsItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PTNscene::itemDoubleClicked)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PTNscene::staticMetaObject = { {
    &QGraphicsScene::staticMetaObject,
    qt_meta_stringdata_PTNscene.data,
    qt_meta_data_PTNscene,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PTNscene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PTNscene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PTNscene.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsScene::qt_metacast(_clname);
}

int PTNscene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void PTNscene::nodeInserted(const QPointF & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PTNscene::arcInserted(QGraphicsItem * _t1, QGraphicsItem * _t2, const QPainterPath & _t3, const QString & _t4, PTNscene * _t5, int _t6, QString _t7)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 4
void PTNscene::itemMoved(QGraphicsItem * _t1, const QPointF & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PTNscene::nodeRemoved(QGraphicsItem * _t1, PTNscene * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void PTNscene::arcRemoved(QGraphicsItem * _t1, PTNscene * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void PTNscene::nodesInserted(const QStringList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void PTNscene::itemDoubleClicked(QGraphicsItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
