#ifndef QINFINITY_QTIO_H
#define QINFINITY_QTIO_H

#include <libinfinity/common/inf-io.h>

#include <QObject>
#include <QList>
#include <QMap>

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
        GObject *gobject() const;
    
    private:
        QInfQtIo *m_gobject;
        QMap<int, QtIoWatch*> socketToWatchMap;

};

}

#endif

