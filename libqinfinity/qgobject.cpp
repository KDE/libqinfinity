/*
 * Copyright 2009  Gregory Haynes <greg@greghaynes.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

