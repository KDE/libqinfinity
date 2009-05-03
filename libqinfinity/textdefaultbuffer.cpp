/*
 * Copyright 2009  Gregory Haynes <greg@greghaynes.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

