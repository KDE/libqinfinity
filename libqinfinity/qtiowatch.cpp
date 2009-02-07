#include "qtiowatch.h"

#include <QSocketNotifier>

#include "qtiowatch.moc"

namespace QInfinity
{

QtIoWatch::QtIoWatch( int socket,
    InfIoEvent events,
    InfIoFunc handler,
    void *user_data,
    GDestroyNotify destroy_notify,
    QObject *parent )
    : QObject( parent )
    , m_incomingNotifier( 0 )
    , m_outgoingNotifier( 0 )
    , m_errorNotifier( 0 )
{
}

QtIoWatch::~QtIoWatch()
{
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
    if( enable && !m_incomingNotifier )
    {
        m_incomingNotifier = new QSocketNotifier( m_socket,
            QSocketNotifier::Read,
            this );
        connect( m_incomingNotifier, SIGNAL(activated()),
            this, SLOT(slotIncomingActivated()) );
    }
    else if( !enable && m_incomingNotifier )
    {
        delete m_incomingNotifier;
        m_incomingNotifier = 0;
    }
}

void QtIoWatch::setOutgoingEvent( bool enable )
{
    if( enable && !m_outgoingNotifier )
    {
        m_outgoingNotifier = new QSocketNotifier( m_socket,
            QSocketNotifier::Read,
            this );
        connect( m_outgoingNotifier, SIGNAL(activated()),
            this, SLOT(slotoutgoingActivated()) );
    }
    else if( !enable && m_outgoingNotifier )
    {
        delete m_outgoingNotifier;
        m_incomingNotifier = 0;
    }
}

void QtIoWatch::setErrorEvent( bool enable )
{
    if( enable && !m_errorNotifier )
    {
        m_errorNotifier = new QSocketNotifier( m_socket,
            QSocketNotifier::Read,
            this );
        connect( m_errorNotifier, SIGNAL(activated()),
            this, SLOT(slotErrorActivated()) );
    }
    else if( !enable && m_errorNotifier )
    {
        delete m_errorNotifier;
        m_errorNotifier = 0;
    }
}

void QtIoWatch::incomingActivated()
{
    m_handler( &m_socket, INF_IO_INCOMING, m_user_data );
}

void QtIoWatch::outgoingActivated()
{
    m_handler( &m_socket, INF_IO_OUTGOING, m_user_data );
}

void QtIoWatch::errorActivated()
{
    m_handler( &m_socket, INF_IO_ERROR, m_user_data );
}

}

