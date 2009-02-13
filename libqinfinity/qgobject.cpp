#include "qgobject.h"
#include "wrapperstore.h"

namespace QInfinity
{

QGObject::QGObject( QObject *parent )
    : QObject( parent )
    , m_gobject( 0 )
    , m_own_gobj( 0 )
{
}

QGObject::QGObject( GObject *obj,
    bool own_gobj,
    QObject *parent )
    : QObject( parent )
    , m_gobject( obj )
    , m_own_gobj( own_gobj )
{
    WrapperStore *store = WrapperStore::instance();
    store->storeWrapper( obj, this, true );
}

QGObject::~QGObject()
{
    if( m_own_gobj && m_gobject )
        g_object_unref( m_gobject );
}

GObject *QGObject::gobject() const
{
    return m_gobject;
}

void QGObject::setGobject( GObject *obj,
    bool own_gobj )
{
    m_gobject = obj;
    m_own_gobj = own_gobj;
    WrapperStore *store = WrapperStore::instance();
    store->storeWrapper( obj, this, true );
}

}

