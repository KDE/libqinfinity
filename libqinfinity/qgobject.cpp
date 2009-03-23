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
    WrapperStore::insertWrapper( this );
}

bool QGObject::isOwner()
{
    return m_own_gobj;
}

QGObject::QGObject( GObject *obj,
    QObject *parent,
    bool own_gobj )
    : QObject( parent )
    , m_gobject( obj )
    , m_own_gobj( own_gobj )
{
    WrapperStore::insertWrapper( this );
}

}

