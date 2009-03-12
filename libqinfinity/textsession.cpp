#include "textsession.h"
#include "wrapperstore.h"
#include "qtio.h"
#include "textbuffer.h"
#include "communicationmanager.h"
#include "communicationjoinedgroup.h"
#include "xmlconnection.h"

namespace QInfinity
{

TextSession *TextSession::create( InfTextSession *infSession,
    QObject *parent )
{
    WrapperStore *store = WrapperStore::instance();
    TextSession *session = dynamic_cast<TextSession*>(store->findWrapper( G_OBJECT(infSession) ));
    if( !session )
        session = new TextSession( infSession, parent );
    return session;
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
    return TextBuffer::create( INF_TEXT_BUFFER( inf_session_get_buffer( INF_SESSION(gobject()) ) ) );
}

TextSession::TextSession( InfTextSession *infSession,
    QObject *parent )
    : Session( INF_SESSION(infSession), parent )
{
}

}

