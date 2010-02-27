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

#ifndef QINFINITY_SESSION_H
#define QINFINITY_SESSION_H

#include "qgobject.h"
#include "communicationmanager.h"
#include "user.h"

#include <libinfinity/common/inf-session.h>

#include <QObject>
#include <QPointer>

namespace QInfinity
{

class CommunicationManager;
class Buffer;
class UserTable;

/**
 * @brief Represents an editing session.
 */
class Session
    : public QGObject
{
    Q_OBJECT;

    public:
        enum Status
        {
            Synchronizing,
            Running,
            Closed
        };

        enum Type
        {
            BaseSession,
            Text
        };

        static Status infStatusToCpp( InfSessionStatus );
        static InfSessionStatus statusToInf( Status );

        static QPointer<Session> wrap( InfSession *session,
            QObject *parent = 0,
            bool own_gobject = false );

        ~Session();

        CommunicationManager *communicationManager() const;
        void close();
        Status status() const;
        void setUserStatus( User &user, User::Status status );
        virtual Type type() const;
        virtual QPointer<Buffer> buffer() const;
        QPointer<UserTable> userTable() const;

    Q_SIGNALS:
        void closing();
        void synchronizationBegin();
        void synchronizationComplete();
        void synchronizationFailed( GError *error );
        void statusChanged();

    protected:
        Session( InfSession *infSession,
            QObject *parent = 0,
            bool own_gobject = false );

    private:
        void setupSignals();

        void signalClosing();
        void signalSynchronizationBegin();
        void signalSynchronizationComplete();
        void signalSynchronizationFailed( GError* );
        void signalStatusChanged();
        static void close_cb( InfSession *session,
            void *user_data );
        static void synchronization_begin_cb( InfSession *session,
            InfCommunicationGroup *group,
            InfXmlConnection *connection,
            void *user_data );
        static void synchronization_complete_cb( InfSession *session,
            InfXmlConnection *connection,
            void *user_data );
        static void synchronization_failed_cb( InfSession *session,
            InfXmlConnection *connection,
            GError *error,
            void *user_data );
        static void status_changed_cb( InfSession *session,
            const char *property,
            void *user_data );
        
};

}

#endif

