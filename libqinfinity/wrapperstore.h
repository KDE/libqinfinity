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

#ifndef QINFINITY_WRAPPER_STORE
#define QINFINITY_WRAPPER_STORE

#include <QObject>
#include <QMultiHash>
#include <QPointer>

#include <glib-object.h>

namespace QInfinity
{

class QGObject;

/**
 * @brief Maps gobject instances to its QGObject wrapper.
 *
 * The WrapperStore maps GObject instances to their QGObject
 * wrappers.  It also handles deletion of the wrapping
 * QGObject when the wrapped GObject is finalized.
 */
class WrapperStore
    : public QObject
{
    Q_OBJECT;

    public:
        /**
         * @brief Get an instance of the WrapperStore class.
         */
        static WrapperStore *instance();

        static void insertWrapper( QGObject *wrapper );

        static QGObject *getWrapper( GObject *object,
            bool own_gobject = true );

        /**
         * @brief Finds wrapper for obj
         * @return Found wrapper object, or NULL if none fond.
         */
        QGObject *findWrapper( GObject *obj,
            bool own_gobject = true );

        /**
         * @brief Store wrapper for gobject.
         *
         * If wrapper already exists for obj, the current wrapper
         * is deleted.  This can cause errors, so make sure to
         * check for an existing wrapper with findWrapper before
         * calling this.
         */
        void storeWrapper( QGObject *wrapper );

    protected:
        WrapperStore();
        ~WrapperStore();

    private Q_SLOTS:
        void slotWrapperDeleted( QGObject* wrapper );

    private:
        void removeWrapper( QGObject *wrapper );

        /*
         * We can use a single-valued hash here because there
         * should only be one stored wrapper per gobject instance.
         */
        QHash<GObject*, QGObject*> gobjToWrapper;
        QHash<GObject*, QGObject*> gobjToOwnerWrapper;

};

}

#endif

