#include "userrequest.h"

#include "userrequest.moc"

namespace QInfinity
{

UserRequest::UserRequest( InfcUserRequest *infRequest,
    QObject *parent )
    : Request( INFC_REQUEST( infRequest ), parent )
{
    finished_handler = g_signal_connect( gobject(),
        "finished",
        G_CALLBACK(UserRequest::finished_cb),
        this );
}

void UserRequest::finished_cb( InfcUserRequest *infcUserRequest,
    InfUser *user,
    void *user_data )
{
    UserRequest *userRequest = static_cast<UserRequest*>(user_data);
    userRequest->emit_finished( User::wrap( user ) );
}

void UserRequest::emit_finished( QPointer<QInfinity::User> user )
{
    emit( finished( user ) );
}

}

