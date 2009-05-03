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

#ifndef QINFINITY_ABSTRACT_TEXT_BUFFER_H
#define QINFINITY_ABSTRACT_TEXT_BUFFER_H

#include "textbuffer.h"

class QString;

namespace QInfinity
{

class TextChunk;

/**
 * @brief Base class for implementing a text buffer.
 *
 * The AbstractTextBuffer is used to implement a custom
 * TextBuffer.  Most projects using the InfText or similar
 * plugin will find this of use.  You can cause your
 * custom implementation to be used by creating a subclass
 * of NotePlugin which creates the proper subclass.
 *
 * Currently, the AbstractTextBuffer provides the same
 * functionality as a DefaultTextBuffer only with calls to
 * the wrapping virtual functions appended for insert and
 * erase text.  In the future this will likely be changed.
 */
class AbstractTextBuffer
    : public TextBuffer
{
    public:
        /**
         * @brief Used by wrapped GObject
         */
        static void bufferIfaceInit( gpointer g_iface,
            gpointer iface_data );
        /**
         * @brief Used by wrapped GObject
         */
        static void textBufferIfaceInit( gpointer g_iface,
            gpointer iface_data );

        /**
         * @brief Create a text buffer base class.
         */
        AbstractTextBuffer( const QString &encoding,
            QObject *parent = 0 );

        virtual ~AbstractTextBuffer();

    protected:
        /**
         * @brief Called to insert text into buffer.
         *
         * Your implementation must account for all of
         * the text provided by this method, and only
         * for that text.  Not doing so can lead to
         * inconsistancies among users.
         */
        virtual void onInsertText( unsigned int offset,
            const TextChunk &chunk,
            User *user ) = 0;

        /**
         * @brief Called to erase text from buffer.
         */
        virtual void onEraseText( unsigned int offset,
            unsigned int length,
            User *user ) = 0;

    private:
        static void insert_text_cb( InfTextBuffer *buffer,
            unsigned int offset,
            InfTextChunk *chunk,
            InfUser *user );
        static void erase_text_cb( InfTextBuffer *buffer,
            unsigned int offset,
            unsigned int length,
            InfUser *user );

};

}

G_BEGIN_DECLS

#define QINF_TEXT_TYPE_ABSTRACT_BUFFER                 (qinf_text_abstract_buffer_get_type())
#define QINF_TEXT_ABSTRACT_BUFFER(obj)                 (G_TYPE_CHECK_INSTANCE_CAST((obj), QINF_TEXT_TYPE_ABSTRACT_BUFFER, QInfTextAbstractBuffer))
#define QINF_TEXT_ABSTRACT_BUFFER_CLASS(klass)         (G_TYPE_CHECK_CLASS_CAST((klass), QINF_TEXT_TYPE_ABSTRACT_BUFFER, QInfTextAbstractBufferClass))
#define QINF_TEXT_IS_ABSTRACT_BUFFER(obj)              (G_TYPE_CHECK_INSTANCE_TYPE((obj), QINF_TEXT_TYPE_ABSTRACT_BUFFER))
#define QINF_TEXT_IS_ABSTRACT_BUFFER_CLASS(klass)      (G_TYPE_CHECK_CLASS_TYPE((klass), QINF_TEXT_TYPE_ABSTRACT_BUFFER))
#define QINF_TEXT_ABSTRACT_BUFFER_GET_CLASS(obj)       (G_TYPE_INSTANCE_GET_CLASS((obj), QINF_TEXT_TYPE_ABSTRACT_BUFFER, QInfTextAbstractBufferClass))

typedef struct _QInfTextAbstractBufferClass QInfTextAbstractBufferClass;
typedef struct _QInfTextAbstractBuffer QInfTextAbstractBuffer;

struct _QInfTextAbstractBufferClass
{
    GObjectClass parent_class;
};

struct _QInfTextAbstractBuffer
{
    GObject parent;
};

GType
qinf_text_abstract_buffer_get_type(void) G_GNUC_CONST;

QInfTextAbstractBuffer*
qinf_text_abstract_buffer_new(const gchar* encoding);

G_END_DECLS

#endif
