#include "qgobject.h"

namespace QInfinity
{

QGObject::QGObject()
    : m_gobject( 0 )
    , m_own_gobj( 0 )
{
}

QGObject::QGObject( GObject *obj,
    bool own_gobj )
    : m_gobject( obj )
    , m_own_gobj( own_gobj )
{
}

QGObject::~QGObject()
{
    if( m_own_gobj && m_gobject )
        delete m_gobject;
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
}

}

