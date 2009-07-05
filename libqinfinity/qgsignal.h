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

#include <QObject>

#include <glib-object.h>

namespace QInfinity
{

class QGObject;
class QGSignalData;

/**
 * @brief GObject signal wrapper which adds intance-checking.
 */
class QGSignal
    : public QObject
{

    public:
        QGSignal( QGObject *instance,
            const char *gsignal_name,
            GCallback callback,
            void *data,
               QObject *parent = 0 );
        ~QGSignal();

    private:
        QGSignalData *d;

};

}

