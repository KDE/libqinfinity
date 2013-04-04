/*
 * Copyright 2009  Gregory Haynes <greg@greghaynes.net>
 * Copyright 2013  Sven Brauch <svenbrauch@gmail.com>
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

class QGObjectPrivate
{
    public:
        GObject *gobject;
        bool own_gobj;
};

QGObject::QGObject( QObject *parent )
    : QObject( parent )
    , d_ptr( new QGObjectPrivate )
{
    Q_D(QGObject);
    
    d->gobject = 0;
    d->own_gobj = 0;
}

QGObject::~QGObject()
{
    Q_D(QGObject);
    emit aboutToDestroy(this);
    
    if( d->own_gobj && d->gobject )
        if( G_IS_OBJECT(d->gobject) )
            g_object_unref( d->gobject );
    delete d;
}

GObject *QGObject::gobject() const
{
    Q_D(const QGObject);
    
    return d->gobject;
}

void QGObject::setGobject( GObject *obj,
    bool own_gobj )
{
    Q_D(QGObject);
    
    d->gobject = obj;
    d->own_gobj = own_gobj;
    WrapperStore::insertWrapper( this );
}

bool QGObject::isOwner() const
{
    Q_D(const QGObject);
    
    return d->own_gobj;
}

QGObject::QGObject( GObject *obj,
    QObject *parent,
    bool own_gobj )
    : QObject( parent )
    , d_ptr( new QGObjectPrivate )
{
    Q_D(QGObject);
    
    d->gobject = obj;
    d->own_gobj = own_gobj;
    WrapperStore::insertWrapper( this );
}

}

#include "qgobject.moc"



