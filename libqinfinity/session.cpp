#include "session.h"
#include "buffer.h"
#include "wrapperstore.h"

#include "session.moc"

namespace QInfinity
{

Session *Session::create( InfSession *infSession,
    QObject *parent )
{
    WrapperStore *store = WrapperStore::instance();
    Session *session = dynamic_cast<Session*>(store->findWrapper( G_OBJECT(infSession) ));
    if( !session )
        session = new Session( infSession, parent );
    return session;
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

Session::Session( InfSession *infSession,
    QObject *parent )
    : QGObject( G_OBJECT(infSession), false, parent )
{
    setupSignals();
}

CommunicationManager *Session::communicationManager() const
{
    InfCommunicationManager *commMgr;

    commMgr = inf_session_get_communication_manager( INF_SESSION(gobject()) );
    return CommunicationManager::create( commMgr );
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

Session::Type Session::type() const
{
    return BaseSession;
}

Buffer *Session::buffer() const
{
    return Buffer::create( inf_session_get_buffer( INF_SESSION(gobject()) ) );
}

void Session::setupSignals()
{
    g_signal_connect( G_OBJECT(gobject()),
        "close", G_CALLBACK(Session::close_cb),
        this );
    g_signal_connect( G_OBJECT(gobject()),
        "synchronization-begin", G_CALLBACK(Session::synchronization_begin_cb),
        this );
    g_signal_connect( G_OBJECT(gobject()),
        "synchronization-complete", G_CALLBACK(Session::synchronization_complete_cb),
        this );
    g_signal_connect( G_OBJECT(gobject()),
        "synchronization-failed", G_CALLBACK(Session::synchronization_failed_cb),
        this );
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

}

