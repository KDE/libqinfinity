#ifndef QINFINITY_NOTE_PLUGIN_H
#define QINFINITY_NOTE_PLUGIN_H

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
            CommunicationJoinedGroup *syncGroup,
            XmlConnection *syncConnection ) = 0;

        /**
         * @brief Get underlying note plugin.
         */
        InfcNotePlugin *infPlugin();
    
    private:
        static InfSession *create_session_cb( InfIo *io,
            InfCommunicationManager *comm_mgr,
            InfCommunicationJoinedGroup *sync_group,
            InfXmlConnection *sync_connection,
            void *user_data );

        char *m_name;
        InfcNotePlugin m_infPlugin;

};

}

#endif

