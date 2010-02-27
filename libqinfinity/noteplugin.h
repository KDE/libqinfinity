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

#ifndef QINFINITY_NOTE_PLUGIN_H
#define QINFINITY_NOTE_PLUGIN_H

#include "session.h"

#include <libinfinity/client/infc-note-plugin.h>

#include <QObject>
#include <QString>

namespace QInfinity
{

class Session;
class CommunicationManager;
class CommunicationJoinedGroup;
class XmlConnection;

/**
 * @brief Note plugin base class used to create sessions.
 *
 * The note plugin is used to create the correct Session
 * and Buffer subclasses for a note.  This is done by
 * overriding the createSession method.
 */
class NotePlugin
    : public QObject
{

    public:
        NotePlugin( QString name, QObject *parent = 0 );
        virtual ~NotePlugin();

        /**
         * @brief Create a new Sesion.
         *
         * All sub classes should re-implement this method to wrap
         * a GObject subclass of InfSession with the apropriate
         * QGObject wrapper.  This method will be called when attempting
         * to join a session using a Browser.
         */
        virtual Session *createSession( CommunicationManager *commMgr,
            Session::Status sess_status,
            CommunicationJoinedGroup *syncGroup,
            XmlConnection *syncConnection ) = 0;

        /**
         * @brief Get underlying note plugin.
         */
        InfcNotePlugin *infPlugin();
    
    private:
        static InfSession *create_session_cb( InfIo *io,
            InfCommunicationManager *comm_mgr,
            InfSessionStatus status,
            InfCommunicationJoinedGroup *sync_group,
            InfXmlConnection *sync_connection,
            void *user_data );

        char *m_name;
        InfcNotePlugin m_infPlugin;

};

}

#endif

