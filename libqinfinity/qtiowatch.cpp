#include "qtiowatch.h"

#include <QAbstractEventDispatcher>

#include "qtiowatch.moc"

#include <QDebug>

namespace QInfinity
{

QtIoWatch::QtIoWatch( int socket,
    InfIoEvent events,
    InfIoFunc handler,
    void *user_data,
    GDestroyNotify destroy_notify,
    QObject *parent )
    : QObject( parent )
    , m_socket( socket )
    , m_handler( handler )
    , m_user_data( user_data )
    , m_incomingNotifier( 0 )
    , m_outgoingNotifier( 0 )
    , m_errorNotifier( 0 )
{
    setEvents( events );
}

QtIoWatch::~QtIoWatch()
{
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
    m_outgoingNotifier->setEnabled( false );
}

void QtIoWatch::errorActivated( int socket )
{
    m_handler( &m_socket, INF_IO_ERROR, m_user_data );
}

}

