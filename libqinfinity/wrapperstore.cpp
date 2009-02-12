#include "wrapperstore.h"
#include "qgobject.h"

#include "wrapperstore.moc"

namespace QInfinity
{

WrapperStore *WrapperStore::instance()
{
    static WrapperStore *store = new WrapperStore;
    return store;
}

QGObject *WrapperStore::findWrapper( GObject *obj )
{
    return wrapperMap[obj];
}

void WrapperStore::storeWrapper( GObject *obj, QGObject *wrapper )
{
    wrapperMap[obj] = wrapper;
    gobjMap[wrapper] = obj;
}

QGObject *WrapperStore::takeWrapper( GObject *obj )
{
    QGObject *qobj = wrapperMap.take( obj );
    gobjMap[qobj] = 0;
    return qobj;
}

WrapperStore::WrapperStore()
{
}

void WrapperStore::wrapperDestroyed( QObject *obj )
{
    if( !obj )
        return;
    QGObject *qobj = dynamic_cast<QGObject*>(obj);
    GObject *gobj = gobjMap[qobj];
    if( !gobj )
        return;
    wrapperMap[gobj] = 0;
    gobjMap[qobj] = 0;
}

}

