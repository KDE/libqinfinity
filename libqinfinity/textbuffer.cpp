#include "textbuffer.h"
#include "wrapperstore.h"

namespace QInfinity
{

TextBuffer *TextBuffer::create( InfTextBuffer *infBuffer,
    QObject *parent )
{
    WrapperStore *store = WrapperStore::instance();
    TextBuffer *buffer = dynamic_cast<TextBuffer*>(store->findWrapper( G_OBJECT(infBuffer) ));
    if( !buffer )
        buffer = new TextBuffer( infBuffer, parent );
    return buffer;
}

TextBuffer::TextBuffer( InfTextBuffer *infBuffer,
    QObject *parent )
    : Buffer( INF_BUFFER(infBuffer), parent )
{
}

}

