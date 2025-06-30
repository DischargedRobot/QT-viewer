/****************************************************************************
** Meta object code from reading C++ file 'scena.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../scena.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scena.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CustomScene_t {
    QByteArrayData data[15];
    char stringdata0[192];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CustomScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CustomScene_t qt_meta_stringdata_CustomScene = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CustomScene"
QT_MOC_LITERAL(1, 12, 22), // "signalTargetCoordinate"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5), // "point"
QT_MOC_LITERAL(4, 42, 18), // "signalSelectedArea"
QT_MOC_LITERAL(5, 61, 6), // "pixmap"
QT_MOC_LITERAL(6, 68, 6), // "xStart"
QT_MOC_LITERAL(7, 75, 4), // "xEnd"
QT_MOC_LITERAL(8, 80, 6), // "yStart"
QT_MOC_LITERAL(9, 87, 4), // "yEnd"
QT_MOC_LITERAL(10, 92, 24), // "signalMousePressSelected"
QT_MOC_LITERAL(11, 117, 10), // "startPoint"
QT_MOC_LITERAL(12, 128, 23), // "signalMouseMoveSelected"
QT_MOC_LITERAL(13, 152, 12), // "currentPoint"
QT_MOC_LITERAL(14, 165, 26) // "signalMouseReleaseSelected"

    },
    "CustomScene\0signalTargetCoordinate\0\0"
    "point\0signalSelectedArea\0pixmap\0xStart\0"
    "xEnd\0yStart\0yEnd\0signalMousePressSelected\0"
    "startPoint\0signalMouseMoveSelected\0"
    "currentPoint\0signalMouseReleaseSelected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CustomScene[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    5,   42,    2, 0x06 /* Public */,
      10,    1,   53,    2, 0x06 /* Public */,
      12,    2,   56,    2, 0x06 /* Public */,
      14,    0,   61,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPointF,    3,
    QMetaType::Void, QMetaType::QPixmap, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    5,    6,    7,    8,    9,
    QMetaType::Void, QMetaType::QPoint,   11,
    QMetaType::Void, QMetaType::QPoint, QMetaType::QPoint,   11,   13,
    QMetaType::Void,

       0        // eod
};

void CustomScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CustomScene *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->signalTargetCoordinate((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 1: _t->signalSelectedArea((*reinterpret_cast< QPixmap(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 2: _t->signalMousePressSelected((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 3: _t->signalMouseMoveSelected((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QPoint(*)>(_a[2]))); break;
        case 4: _t->signalMouseReleaseSelected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CustomScene::*)(QPointF );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomScene::signalTargetCoordinate)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CustomScene::*)(QPixmap , int , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomScene::signalSelectedArea)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CustomScene::*)(QPoint );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomScene::signalMousePressSelected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CustomScene::*)(QPoint , QPoint );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomScene::signalMouseMoveSelected)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CustomScene::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomScene::signalMouseReleaseSelected)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CustomScene::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsScene::staticMetaObject>(),
    qt_meta_stringdata_CustomScene.data,
    qt_meta_data_CustomScene,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CustomScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CustomScene.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsScene::qt_metacast(_clname);
}

int CustomScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CustomScene::signalTargetCoordinate(QPointF _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CustomScene::signalSelectedArea(QPixmap _t1, int _t2, int _t3, int _t4, int _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CustomScene::signalMousePressSelected(QPoint _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CustomScene::signalMouseMoveSelected(QPoint _t1, QPoint _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CustomScene::signalMouseReleaseSelected()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
