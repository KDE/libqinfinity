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

#ifndef QINFINITY_BUFFER_H
#define QINFINITY_BUFFER_H

#include "qgobject.h"

#include <QPointer>

typedef struct _InfBuffer InfBuffer;

namespace QInfinity
{

/**
 * @brief A base buffer for collaborative editing.
 *
 * You probably want to look at a subclass of this,
 * such as TextBuffer or AbstractTextBuffer.
 */
class Buffer
    : public QGObject
{

    public:
        static QPointer<Buffer> wrap( InfBuffer *buffer,
            QObject *parent = 0,
            bool own_gobject = false );

    protected:
        Buffer( InfBuffer *buffer,
            QObject *parent = 0,
            bool own_gobject = false );

};

}

#endif

