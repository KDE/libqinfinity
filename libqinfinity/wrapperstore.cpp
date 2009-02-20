#include "wrapperstore.h"
#include "qgobject.h"

#include "wrapperstore.moc"

#include <QDebug>

namespace QInfinity
{

WrapperStore *WrapperStore::instance()
{
    static WrapperStore store;
    return &store;
}

QGObject *WrapperStore::findWrapper( GObject *obj )
{
    QPointer<QGObject> qgobj_ptr = gobjToWrapper[obj];
    if( qgobj_ptr )
        return qgobj_ptr.data();
    else
        return 0;
}

void WrapperStore::storeWrapper( GObject *obj,
    QGObject *wrapper,
    bool own_wrapper )
{
    gobjToWrapper[obj] = wrapper;
}

WrapperStore::WrapperStore()
{
}

WrapperStore::~WrapperStore()
{
}

}

