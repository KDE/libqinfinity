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

QGObject *WrapperStore::getWrapper( GObject *object,
    bool own_gobject )
{
    WrapperStore *store = WrapperStore::instance();
    return store->findWrapper( object, own_gobject );
}

QGObject *WrapperStore::findWrapper( GObject *obj,
    bool own_gobject )
{
    if( own_gobject )
    {
        if( gobjToOwnerWrapper.contains( obj ) )
            return gobjToOwnerWrapper[obj];
    }
    else
    {
        if( gobjToWrapper.contains( obj ) )
            return gobjToWrapper[obj];
    }
    return 0;
}

void WrapperStore::storeWrapper( GObject *obj,
    QGObject *wrapper )
{
    QGObject *old_wrapper;
    QHash<GObject*, QGObject*> *table;
    if( wrapper->isOwner() )
        table = &gobjToOwnerWrapper;
    else
        table = &gobjToWrapper;
    if( table->contains( obj ) )
    {
        old_wrapper = (*table)[obj];
        removeWrapper( old_wrapper );
        delete old_wrapper;
    }
    (*table)[obj] = wrapper;
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
    if( wrapper )
        removeWrapper( dynamic_cast<QGObject*>(wrapper) );
}

void WrapperStore::removeWrapper( QGObject *wrapper )
{
    if( !wrapper )
        return;
    if( wrapper->isOwner() )
        gobjToOwnerWrapper.remove( wrapper->gobject() );
    gobjToWrapper.remove( wrapper->gobject() );
}

}

