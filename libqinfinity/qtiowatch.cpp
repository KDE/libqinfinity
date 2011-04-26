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

#include "qtiowatch.h"

#include <QAbstractEventDispatcher>

#include "qtiowatch.moc"

#include <QDebug>

namespace QInfinity
{

QtIoWatch::QtIoWatch( int socket,
    InfIoEvent events,
    InfIoWatchFunc handler,
    void *user_data,
    GDestroyNotify destroy_notify,
    QObject *parent )
    : QObject( parent )
    , m_socket( socket )
    , m_handler( handler )
    , m_user_data( user_data )
    , m_destroy_notify( destroy_notify )
    , m_incomingNotifier( 0 )
    , m_outgoingNotifier( 0 )
    , m_errorNotifier( 0 )
{
    setEvents( events );
}

QtIoWatch::~QtIoWatch()
{
    if( m_incomingNotifier )
        delete m_incomingNotifier;
    if( m_outgoingNotifier )
        delete m_outgoingNotifier;
    if( m_errorNotifier )
        delete m_errorNotifier;
    if( m_destroy_notify )
        m_destroy_notify( m_user_data );
}

void QtIoWatch::setEvents( InfIoEvent events )
{
    if( events & INF_IO_INCOMING )
        setIncomingEvent( true );
    else
        setIncomingEvent( false );

    if( events & INF_IO_OUTGOING )
        setOutgoingEvent( true );
    else
        setOutgoingEvent( false );
    
    if( events & INF_IO_ERROR )
        setErrorEvent( true );
    else
        setErrorEvent( false );
}

void QtIoWatch::setIncomingEvent( bool enable )
{
    if( enable )
    {
        if( !m_incomingNotifier )
        {
            m_incomingNotifier = new QSocketNotifier( m_socket,
                QSocketNotifier::Read,
                this );
            connect( m_incomingNotifier, SIGNAL(activated(int)),
                this, SLOT(incomingActivated(int)) );
        }

        m_incomingNotifier->setEnabled( true );
    }
    else if( m_incomingNotifier )
    {
        m_incomingNotifier->setEnabled( false );
    }
}

void QtIoWatch::setOutgoingEvent( bool enable )
{
    if( enable )
    {
        if( !m_outgoingNotifier )
        {
            m_outgoingNotifier = new QSocketNotifier( m_socket,
                QSocketNotifier::Write,
                this );
            connect( m_outgoingNotifier, SIGNAL(activated(int)),
                this, SLOT(outgoingActivated(int)) );
        }

        m_outgoingNotifier->setEnabled( true );
    }
    else if( m_outgoingNotifier )
    {
        m_outgoingNotifier->setEnabled( false );
    }
}

void QtIoWatch::setErrorEvent( bool enable )
{
    if( enable )
    {
        if( !m_errorNotifier )
        {
            m_errorNotifier = new QSocketNotifier( m_socket,
                QSocketNotifier::Exception,
                this );
            connect( m_errorNotifier, SIGNAL(activated(int)),
                this, SLOT(errorActivated(int)) );
        }

        m_errorNotifier->setEnabled( true );
    }
    else if( m_errorNotifier )
    {
        m_errorNotifier->setEnabled( false );
    }
}

void QtIoWatch::incomingActivated( int socket )
{
    m_handler( &m_socket, INF_IO_INCOMING, m_user_data );
}

void QtIoWatch::outgoingActivated( int socket )
{
    m_handler( &m_socket, INF_IO_OUTGOING, m_user_data );
}

void QtIoWatch::errorActivated( int socket )
{
    m_handler( &m_socket, INF_IO_ERROR, m_user_data );
}

}

