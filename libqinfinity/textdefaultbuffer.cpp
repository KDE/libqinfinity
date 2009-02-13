#include "textdefaultbuffer.h"

#include <libinftext/inf-text-default-buffer.h>

namespace QInfinity
{

TextDefaultBuffer::TextDefaultBuffer( QString encoding,
    QObject *parent )
    : TextBuffer( INF_TEXT_BUFFER(inf_text_default_buffer_new( encoding.toAscii() )), parent )
{
}

}

