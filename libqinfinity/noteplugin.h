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
 * If you plan on using a subclass of Session, you must re-implement
 * the createSession method in a subclass of this to create the
 * session subclass you would like to use.  See createSession for
 * more information.
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
         * If you plan on using a subclass of Session (rather than the
         * gobject instances) you must re-implement this to create
         * the proper Session subclass.  This allows your session to
         * be added to the shared object store for retrieval from the
         * SessionProxy and Browser subclasses.  If this is not done you
         * will always receive a base Session class.
         */
        virtual Session *createSession( CommunicationManager *commMgr,
            CommunicationJoinedGroup *syncGroup,
            XmlConnection *syncConnection ) = 0;

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

