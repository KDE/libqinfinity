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

#include "session.h"
#include "buffer.h"
#include "usertable.h"
#include "wrapperstore.h"
#include "qgsignal.h"

#include <QDebug>

#include "session.moc"

namespace QInfinity
{

QPointer<Session> Session::wrap( InfSession *infObj,
    QObject *parent,
    bool own_gobject )
{
    QGObject *wrapptr = WrapperStore::getWrapper( G_OBJECT(infObj), own_gobject );
    if( wrapptr)
        return dynamic_cast<Session*>(wrapptr);
    Session *wrapper = new Session( infObj, parent, own_gobject );
    return wrapper;
}

Session::Status Session::infStatusToCpp( InfSessionStatus infStatus )
{
    Status status;

    switch( infStatus )
    {
        case INF_SESSION_SYNCHRONIZING:
            status = Synchronizing;
            break;
        case INF_SESSION_RUNNING:
            status = Running;
            break;
        default:
            status = Closed;
    }

    return status;
}

InfSessionStatus Session::statusToInf( Status status )
{
    InfSessionStatus infStatus;

    switch( status )
    {
        case Synchronizing:
            infStatus = INF_SESSION_SYNCHRONIZING;
            break;
        case Running:
            infStatus = INF_SESSION_RUNNING;
            break;
        default:
            infStatus = INF_SESSION_CLOSED;
    }

    return infStatus;
}

Session::~Session()
{
}

CommunicationManager *Session::communicationManager() const
{
    InfCommunicationManager *commMgr;

    commMgr = inf_session_get_communication_manager( INF_SESSION(gobject()) );
    return CommunicationManager::wrap( commMgr );
}

void Session::close()
{
    inf_session_close( INF_SESSION(gobject()) );
}

Session::Status Session::status() const
{
    return Session::infStatusToCpp(
        inf_session_get_status( INF_SESSION(gobject()) ) );
}

void Session::setUserStatus( User &user, User::Status status )
{
    inf_session_set_user_status( INF_SESSION(gobject()),
        INF_USER(user.gobject()), User::convertStatus( status ) );
}

Session::Type Session::type() const
{
    return BaseSession;
}

QPointer<Buffer> Session::buffer() const
{
    return Buffer::wrap( inf_session_get_buffer( INF_SESSION(gobject()) ) );
}

QPointer<UserTable> Session::userTable() const
{
    return UserTable::wrap( inf_session_get_user_table( INF_SESSION(gobject()) ) );
}

Session::Session( InfSession *infSession,
    QObject *parent,
    bool own_gobject )
    : QGObject( G_OBJECT(infSession), parent, own_gobject )
{
    setupSignals();
}

void Session::setupSignals()
{
    new QGSignal( this, "close",
        G_CALLBACK(Session::close_cb), this, this );
    new QGSignal( this, "synchronization-begin",
        G_CALLBACK(Session::synchronization_begin_cb), this, this );
    new QGSignal( this, "synchronization-complete",
        G_CALLBACK(Session::synchronization_complete_cb), this, this );
    new QGSignal( this, "synchronization-failed",
        G_CALLBACK(Session::synchronization_failed_cb), this, this );
    new QGSignal( this, "notify::status",
        G_CALLBACK(Session::status_changed_cb), this, this );
}

void Session::signalClosing()
{
    emit(closing());
}

void Session::signalSynchronizationBegin()
{
    emit(synchronizationBegin());
}

void Session::signalSynchronizationComplete()
{
    emit(synchronizationComplete());
}

void Session::signalSynchronizationFailed( GError *error )
{
    emit(synchronizationFailed( error ));
}

void Session::signalStatusChanged()
{
    emit(statusChanged());
}

void Session::close_cb( InfSession *session,
    void *user_data )
{
    static_cast<Session*>(user_data)->signalClosing();
}

void Session::synchronization_begin_cb( InfSession *session,
    InfCommunicationGroup *group,
    InfXmlConnection *connection,
    void *user_data )
{
    static_cast<Session*>(user_data)->signalSynchronizationBegin();
}

void Session::synchronization_complete_cb( InfSession *session,
    InfXmlConnection *connection,
    void *user_data )
{
    static_cast<Session*>(user_data)->signalSynchronizationComplete();
}

void Session::synchronization_failed_cb( InfSession *session,
    InfXmlConnection* connection,
    GError *error,
    void *user_data )
{
    static_cast<Session*>(user_data)->signalSynchronizationFailed( error );
}

void Session::status_changed_cb( InfSession *session,
    const char *property,
    void *user_data )
{
    static_cast<Session*>(user_data)->signalStatusChanged();
}

}

