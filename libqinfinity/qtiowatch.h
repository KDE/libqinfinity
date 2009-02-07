#ifndef QINFINITY_QTIOWATCH_H
#define QINFINITY_QTIOWATCH_H

#include <libinfinity/common/inf-io.h>

#include <QObject>

class QSocketNotifier;

namespace QInfinity
{

/**
 * @brief Handles creation of all notifiers for a given socket.
 */
class QtIoWatch
    : public QObject
{
    Q_OBJECT

    public:
        QtIoWatch( int socket,
            InfIoEvent events,
            InfIoFunc handler,
            void *user_data,
            GDestroyNotify destroy_notify,
               QObject *parent = 0 );
        ~QtIoWatch();

        void setEvents( InfIoEvent events );
        void setIncomingEvent( bool enable );
        void setOutgoingEvent( bool enable );
        void setErrorEvent( bool enable );
    
    private Q_SLOTS:
        void incomingActivated();
        void outgoingActivated();
        void errorActivated();

    private:
        int m_socket;
        InfIoFunc m_handler;
        void *m_user_data;
        GDestroyNotify m_destroy_notify;

        /* Because there are so few event types, we may as
         * well hard code pointers for efficiency's sake. */
        QSocketNotifier *m_incomingNotifier;
        QSocketNotifier *m_outgoingNotifier;
        QSocketNotifier *m_errorNotifier;

};

}

#endif

