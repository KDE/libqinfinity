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

#ifndef QINFINITY_QTIO_H
#define QINFINITY_QTIO_H

#include <libinfinity/common/inf-io.h>

#include <QObject>
#include <QList>
#include <QHash>
#include <QTimer>

namespace QInfinity
{

class QtIo;
class QtIoWatch;

typedef struct _QInfQtIoClass QInfQtIoClass;
typedef struct _QInfQtIo QInfQtIo;

/**
 * @brief Event handler interface for libinfinity.
 */
class QtIo
    : public QObject
{

    public:
        static QtIo *instance();

        QtIo( QObject *parent = 0 );
        virtual ~QtIo();

        virtual InfIoWatch *addWatch( InfNativeSocket *socket,
            InfIoEvent events,
            InfIoWatchFunc func,
            gpointer user_data,
            GDestroyNotify notify );
        virtual void updateWatch( InfIoWatch *watch,
            InfIoEvent events );
        virtual void removeWatch( InfIoWatch *watch );

        virtual InfIoTimeout *addTimeout( unsigned int msecs,
            InfIoTimeoutFunc func,
            void *user_data,
            GDestroyNotify notify );
        virtual void removeTimeout( InfIoTimeout *timer );

        virtual InfIoDispatch *addDispatch( InfIoDispatchFunc func,
            gpointer user_data,
            GDestroyNotify notify );
        virtual void removeDispatch( InfIoDispatch *dispatch );

        GObject *gobject() const;
        void setOwner( bool own_gobject );
    
    private:
        QInfQtIo *m_gobject;
        bool own_gobject;
        QHash<int, QtIoWatch*> socketToWatchMap;

};

/**
 * @brief Timer for QtIo
 */
class InfTimer
    :  public QTimer
{
    Q_OBJECT;

    public:
        InfTimer( unsigned int msecs,
            InfIoTimeoutFunc func,
            void *user_data,
            GDestroyNotify notify,
            QObject *parent = 0 );
        ~InfTimer();

        void activate();

    private Q_SLOTS:
        void activated();

    private:
        InfIoTimeoutFunc m_func;
        void *m_user_data;
        GDestroyNotify m_notify;

};

}

#endif

