#ifndef QINFINITY_QTIO_H
#define QINFINITY_QTIO_H

#include <libinfinity/common/inf-io.h>

#include <QObject>
#include <QList>
#include <QHash>
#include <QTimer>

namespace QInfinity
{

class QtIo;
class QtIoWatch;

typedef struct _QInfQtIoClass QInfQtIoClass;
typedef struct _QInfQtIo QInfQtIo;

class QtIo
    : public QObject
{

    public:
        static QtIo *instance();

        QtIo( QObject *parent = 0 );
        virtual ~QtIo();

        virtual void watch( InfNativeSocket *socket,
            InfIoEvent events,
            InfIoFunc func,
            gpointer user_data,
            GDestroyNotify notify );
        virtual void *addTimeout( unsigned int msecs,
            InfIoTimeoutFunc func,
            void *user_data,
            GDestroyNotify notify );
        virtual void removeTimeout( void *timer );
        GObject *gobject() const;
        void setOwner( bool own_gobject );
    
    private:
        QInfQtIo *m_gobject;
        bool own_gobject;
        QHash<int, QtIoWatch*> socketToWatchMap;

};

class InfTimer
    :  public QTimer
{
    Q_OBJECT;

    public:
        InfTimer( unsigned int msecs,
            InfIoTimeoutFunc func,
            void *user_data,
            GDestroyNotify notify,
            QObject *parent = 0 );
        ~InfTimer();

        void activate();

    private Q_SLOTS:
        void activated();

    private:
        InfIoTimeoutFunc m_func;
        void *m_user_data;
        GDestroyNotify m_notify;

};

}

#endif

