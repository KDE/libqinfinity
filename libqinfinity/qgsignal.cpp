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

#include "qgsignal.h"
#include "qgobject.h"

#include <QPointer>

namespace QInfinity
{

class QGSignalData
{

    public:
        QPointer<QGObject> qgobject;
        gulong handlerId;

};

QGSignal::QGSignal( QGObject *instance,
    const char *gsignal_name,
    GCallback callback,
    void *data,
    QObject *parent )
    : QObject( parent )
    , d( new QGSignalData )
{
    d->qgobject = instance;
    if( d->qgobject )
    {
        d->handlerId = g_signal_connect( d->qgobject->gobject(),
            gsignal_name,
            callback,
            data );
    }
    else
    {
        d->handlerId = 0;
    }
}

QGSignal::~QGSignal()
{
    if( d->qgobject && !G_IS_OBJECT(d->qgobject->gobject())
        && d->handlerId )
        g_signal_handler_disconnect( d->qgobject->gobject(),
            d->handlerId );
    delete d;
}

}

