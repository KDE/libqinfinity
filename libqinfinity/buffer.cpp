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

#include "buffer.h"
#include "wrapperstore.h"

namespace QInfinity
{

QPointer<Buffer> Buffer::wrap( InfBuffer *infBuffer,
    QObject *parent,
    bool own_gobject )
{
    QGObject *wrapptr = WrapperStore::getWrapper( G_OBJECT(infBuffer), own_gobject );
    if( wrapptr)
        return dynamic_cast<Buffer*>(wrapptr);
    Buffer *buffer = new Buffer( infBuffer, parent, own_gobject );
    return buffer;
}

Buffer::Buffer( InfBuffer *buffer,
    QObject *parent,
    bool own_gobject )
    : QGObject( G_OBJECT(buffer), parent, own_gobject )
{
}

}

