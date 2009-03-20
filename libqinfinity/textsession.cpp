#include "textsession.h"
#include "wrapperstore.h"
#include "qtio.h"
#include "textbuffer.h"
#include "communicationmanager.h"
#include "communicationjoinedgroup.h"
#include "xmlconnection.h"

#include <libinfinity/client/infc-session-proxy.h>

#include <glib-object.h>

namespace QInfinity
{
 
QPointer<TextSession> TextSession::wrap( InfTextSession *infObject,
    QObject *parent,
    bool own_gobject )
{
    QGObject *wrapptr = WrapperStore::getWrapper( G_OBJECT(infObject), own_gobject );
    if( wrapptr)
        return dynamic_cast<TextSession*>(wrapptr);
    TextSession *wrapper = new TextSession( infObject, parent, own_gobject );
    WrapperStore::insertWrapper( G_OBJECT(infObject), wrapper );
    return wrapper;
}

InfcUserRequest *TextSession::joinUser( QPointer<SessionProxy> proxy,
    const QString &name,
    double hue,
    unsigned int caretPosition,
    User::Status userStatus )
{
    if( !proxy )
        return 0;

    InfSession *session = INF_SESSION(proxy->session()->gobject());

    GParameter params[5] = {
        { "name", { 0 } },
        { "hue", { 0 } },
        { "vector", { 0 } },
        { "caret-position", { 0 } },
        { "status", { 0 } }
    };

    g_value_init( &params[0].value, G_TYPE_STRING );
    g_value_init( &params[1].value, G_TYPE_DOUBLE );
    g_value_init( &params[2].value, INF_ADOPTED_TYPE_STATE_VECTOR );
    g_value_init( &params[3].value, G_TYPE_UINT );
    g_value_init( &params[4].value, INF_TYPE_USER_STATUS );

    g_value_set_static_string( &params[0].value, name.toAscii() );
    g_value_set_double( &params[1].value, hue );
    g_value_take_boxed( &params[2].value, inf_adopted_state_vector_copy(
        inf_adopted_algorithm_get_current(
            inf_adopted_session_get_algorithm(
                INF_ADOPTED_SESSION( session ) ) ) ) );
    g_value_set_uint( &params[3].value, caretPosition );
    g_value_set_enum( &params[4].value, User::convertStatus( userStatus ) );

    InfcUserRequest *req = infc_session_proxy_join_user( INFC_SESSION_PROXY(proxy->gobject()),
        params, 5, 0 );

    g_value_unset(&params[0].value);
    g_value_unset(&params[1].value);
    g_value_unset(&params[2].value);
    g_value_unset(&params[3].value);
    g_value_unset(&params[4].value);
}

TextSession::TextSession( CommunicationManager &commMgr,
    TextBuffer &textBuffer,
    CommunicationJoinedGroup &commGroup,
    XmlConnection &connection )
    : Session( INF_SESSION(inf_text_session_new( INF_COMMUNICATION_MANAGER(commMgr.gobject()),
            INF_TEXT_BUFFER(textBuffer.gobject()),
            INF_IO(QtIo::instance()->gobject()),
            INF_COMMUNICATION_GROUP(commGroup.gobject()),
            INF_XML_CONNECTION(connection.gobject()) )) )
{
}

Session::Type TextSession::type() const
{
    return Text;
}

QPointer<Buffer> TextSession::buffer() const
{
    QPointer<TextBuffer> textBuff = TextBuffer::wrap( INF_TEXT_BUFFER(
        inf_session_get_buffer( INF_SESSION(gobject()) ) ) );
    return static_cast<QPointer<Buffer> >(textBuff);
}


TextSession::TextSession( InfTextSession *infSession,
    QObject *parent,
    bool own_gobject )
    : Session( INF_SESSION(infSession), parent, own_gobject )
{
}

}

