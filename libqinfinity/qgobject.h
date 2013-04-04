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

#ifndef QINFINITY_QGOBJECT_H
#define QINFINITY_QGOBJECT_H

#include <glib-object.h>

#include <QObject>

namespace QInfinity
{

class QGObjectPrivate;

/**
 * @brief Base class for classes wrapping a gobject
 */
class QGObject
    : public QObject
{
Q_OBJECT
    public:
        QGObject( QObject *parent = 0 );
        ~QGObject();

        GObject *gobject() const;
        void setGobject( GObject *obj,
            bool own_gobj = true );
        bool isOwner() const;

    protected:
        QGObject( GObject *obj,
            QObject *parent = 0,
            bool own_gobj = true );

    private:
        QGObjectPrivate *d_ptr;
        Q_DECLARE_PRIVATE(QGObject)

    signals:
        void aboutToDestroy(QGObject* self);
};

}

#endif

