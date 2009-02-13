#include "wrapperstore.h"
#include "qgobject.h"

#include "wrapperstore.moc"

#include <QDebug>

namespace QInfinity
{

WrapperIndex::WrapperIndex( QGObject *wrapper,
    bool own_object )
    : m_wrapper( wrapper )
    , m_own_object( own_object )
{
}

WrapperIndex::~WrapperIndex()
{
    if( isOwner() )
        delete wrapper();
}

QGObject *WrapperIndex::wrapper() const
{
    return m_wrapper;
}

bool WrapperIndex::isOwner() const
{
    return m_own_object;
}

void WrapperIndex::setOwner( bool own_object )
{
    m_own_object = own_object;
}

WrapperStore *WrapperStore::instance()
{
    static WrapperStore store;
    return &store;
}

QGObject *WrapperStore::findWrapper( GObject *obj )
{
    WrapperIndex *index = findWrapperIndex( obj );
    if( index )
        return index->wrapper();
    else
        return 0;
}

void WrapperStore::storeWrapper( GObject *obj,
    QGObject *wrapper,
    bool own_wrapper )
{
    WrapperIndex *index = findWrapperIndex( obj );
    if( index )
        delete index;
    // We should be overwriting keys so ne need to clear
    connect( wrapper, SIGNAL(destroyed(QObject*)),
        this, SLOT(wrapperDestroyed(QObject*)) );
    index = new WrapperIndex( wrapper, own_wrapper );    
    gobjToWrapperMap[obj] = index;
    qToGobjMap[wrapper] = obj;
}

QGObject *WrapperStore::takeWrapper( GObject *obj )
{
    QGObject *qobj;
    WrapperIndex *index = findWrapperIndex( obj );
    if( !index )
        return 0;
    gobjToWrapperMap.remove( obj );
    qToGobjMap.remove( index->wrapper() );
    qobj = index->wrapper();
    delete index;
    return qobj;
}

WrapperStore::WrapperStore()
{
}

WrapperStore::~WrapperStore()
{
    QList<WrapperIndex*> indexes;
    QList<WrapperIndex*>::Iterator indexItr;

    indexes = gobjToWrapperMap.values();
    for( indexItr = indexes.begin(); indexItr != indexes.end(); indexItr++ )
    {
            delete *indexItr;
    }
}

void WrapperStore::wrapperDestroyed( QObject *obj )
{
    WrapperIndex *index;
    QGObject *qobj = dynamic_cast<QGObject*>(obj);
    GObject *gobj = findGobject( qobj );
    if( !gobj )
    {
        return;
    }
    index = findWrapperIndex( gobj );
    if( !index )
    {
        qDebug() << "Destroy notice from un-indexed GObject.";
        return;
    }
    index->setOwner( false );
    qToGobjMap.remove( qobj );
    gobjToWrapperMap.remove( gobj );
    delete index;
}

WrapperIndex *WrapperStore::findWrapperIndex( GObject *obj )
{
    if( gobjToWrapperMap.contains( obj ) )
        return gobjToWrapperMap[obj];
    else
        return 0;
}

GObject *WrapperStore::findGobject( QGObject *obj )
{
    if( qToGobjMap.contains( obj ) )
        return qToGobjMap[obj];
    else
        return 0;
}

}

