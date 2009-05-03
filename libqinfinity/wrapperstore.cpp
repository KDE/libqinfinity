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

void WrapperStore::insertWrapper( QGObject *wrapper )
{
    WrapperStore *store = WrapperStore::instance();
    store->storeWrapper( wrapper );
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

void WrapperStore::storeWrapper( QGObject *wrapper )
{
    GObject *obj = wrapper->gobject();
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
    {
        // We cant dynamic_cast because the object has been deleted
        removeWrapper( (QGObject*)wrapper );
    }
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

