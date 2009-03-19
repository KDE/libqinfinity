#include "request.h"

#include "request.moc"

namespace QInfinity
{

Request::Request( InfcRequest *infRequest,
    QObject *parent )
    : QGObject( G_OBJECT( infRequest ), parent )
{
    setupSignals();
}

void Request::setupSignals()
{
    g_signal_connect( gobject(), "failed",
        G_CALLBACK(Request::signalFailed_cb), this );
}

void Request::signalFailed( GError *error )
{
    emit( failed( error ) );
}

void Request::signalFailed_cb( InfcRequest *request,
    GError *error,
    void *user_data )
{
    Request *sender = static_cast<Request*>(user_data);
    sender->signalFailed( error );
}

}

