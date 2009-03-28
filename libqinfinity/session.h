#ifndef QINFINITY_SESSION_H
#define QINFINITY_SESSION_H

#include "qgobject.h"
#include "communicationmanager.h"

#include <libinfinity/common/inf-session.h>

#include <QObject>
#include <QPointer>

typedef struct _InfSession InfSession;

namespace QInfinity
{

class CommunicationManager;
class Buffer;

/**
 * @brief Represents an editing session.
 */
class Session
    : public QGObject
{
    Q_OBJECT;

    public:
        enum Status
        {
            Synchronizing,
            Running,
            Closed
        };

        enum Type
        {
            BaseSession,
            Text
        };

        static Status infStatusToCpp( InfSessionStatus );
        static QPointer<Session> wrap( InfSession *session,
            QObject *parent = 0,
            bool own_gobject = false );

        CommunicationManager *communicationManager() const;
        void close();
        Status status() const;
        virtual Type type() const;
        virtual QPointer<Buffer> buffer() const;

    Q_SIGNALS:
        void closing();
        void synchronizationBegin();
        void synchronizationComplete();
        void synchronizationFailed( GError *error );

    protected:
        Session( InfSession *infSession,
            QObject *parent = 0,
            bool own_gobject = false );

    private:
        void setupSignals();

        void signalClosing();
        void signalSynchronizationBegin();
        void signalSynchronizationComplete();
        void signalSynchronizationFailed( GError* );
        static void close_cb( InfSession *session,
            void *user_data );
        static void synchronization_begin_cb( InfSession *session,
            InfCommunicationGroup *group,
            InfXmlConnection *connection,
            void *user_data );
        static void synchronization_complete_cb( InfSession *session,
            InfXmlConnection *connection,
            void *user_data );
        static void synchronization_failed_cb( InfSession *session,
            InfXmlConnection *connection,
            GError *error,
            void *user_data );
        
};

}

#endif

