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
 * The job of the NotePlugin is to create a InfSession derived
 * GObject, as well as a Session derived QGobject to wrap the
 * session.  This allows the wrapping session to be stored in
 * the WrapperStore so the SessionProxy representing the GObject
 * session can retrieve the appropriate wrapper.
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

        QString m_name;
        InfcNotePlugin m_infPlugin;

};

}

#endif

