#ifndef QINFINITY_QTIO_H
#define QINFINITY_QTIO_H

#include <libinfinity/common/inf-io.h>
#include <glib-object.h>

#include <QObject>
#include <QList>
#include <QMap>

namespace QInfinity
{

class QtIo;
class QtIoWatch;

G_BEGIN_DECLS

#define QINF_TYPE_QT_IO                 (qinf_qt_io_get_type())
#define QINF_QT_IO(obj)                    (G_TYPE_CHECK_INSTANCE_CAST((obj), QINF_TYPE_QT_IO, QInfQtIo))

G_END_DECLS

typedef struct _QInfQtIoClass QInfQtIoClass;
typedef struct _QInfQtIo QInfQtIo;

struct _QInfQtIoClass {
    GObjectClass parent_class;
};

struct _QInfQtIo {
    GObject parent;    
    QtIo *cpp_class;
    int destroy_cpp_class;
};


GType qinf_qt_io_get_type();

class QtIo
    : public QObject
{

    public:
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

