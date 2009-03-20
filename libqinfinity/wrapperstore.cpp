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

void WrapperStore::insertWrapper( GObject *object,
    QGObject *wrapper )
{
    WrapperStore *store = WrapperStore::instance();
    store->storeWrapper( object, wrapper );
}

QGObject *WrapperStore::getWrapper( GObject *object )
{
    WrapperStore *store = WrapperStore::instance();
    return store->findWrapper( object );
}

QGObject *WrapperStore::findWrapper( GObject *obj )
{
    if( gobjToWrapper.contains( obj ) )
        return gobjToWrapper[obj];
    return 0;
}

void WrapperStore::storeWrapper( GObject *obj,
    QGObject *wrapper )
{
    QGObject *old_wrapper;
    if( gobjToWrapper.contains( obj ) )
    {
        old_wrapper = gobjToWrapper[obj];
        removeWrapper( old_wrapper );
        delete old_wrapper;
    }
    gobjToWrapper[obj] = wrapper;
    connect( wrapper, SIGNAL(destroyed( QObject* )),
        this, SLOT(slotWrapperDeleted( QObject* )) );
}

WrapperStore::WrapperStore()
{
}

WrapperStore::~WrapperStore()
{
}

void WrapperStore::slotWrapperDeleted( QObject *wrapper )
{
    removeWrapper( dynamic_cast<QGObject*>(wrapper) );
}

void WrapperStore::removeWrapper( QGObject *wrapper )
{
    gobjToWrapper.remove( wrapper->gobject() );
}

}

