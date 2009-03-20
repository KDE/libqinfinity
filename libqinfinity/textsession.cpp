#include "textsession.h"
#include "wrapperstore.h"
#include "qtio.h"
#include "textbuffer.h"
#include "communicationmanager.h"
#include "communicationjoinedgroup.h"
#include "xmlconnection.h"

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

Buffer *TextSession::buffer() const
{
    return TextBuffer::wrap( INF_TEXT_BUFFER( inf_session_get_buffer( INF_SESSION(gobject()) ) ) );
}

TextSession::TextSession( InfTextSession *infSession,
    QObject *parent,
    bool own_gobject )
    : Session( INF_SESSION(infSession), parent, own_gobject )
{
}

}

