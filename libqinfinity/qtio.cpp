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

#include "qtio.h"
#include "qtiowatch.h"

#include <glib-object.h>

#include <QTimer>
#include <QDebug>

#include "qtio.moc"

namespace QInfinity
{

G_BEGIN_DECLS

#define QINF_TYPE_QT_IO                 (qinf_qt_io_get_type())
#define QINF_QT_IO(obj)                    (G_TYPE_CHECK_INSTANCE_CAST((obj), QINF_TYPE_QT_IO, QInfQtIo))

G_END_DECLS

struct _QInfQtIoClass {
    GObjectClass parent_class;
};

struct _QInfQtIo {
    GObject parent;    
    QtIo *cpp_class;
    int destroy_cpp_class;
};

GType qinf_qt_io_get_type();

static GObjectClass *parent_class;

static InfIoWatch* qinf_qt_io_io_add_watch( InfIo *io,
    InfNativeSocket *socket,
    InfIoEvent events,
    InfIoWatchFunc func,
    gpointer user_data,
    GDestroyNotify notify )
{
    InfIoWatch* watch;
    QInfQtIo *qtIo;

    qtIo = QINF_QT_IO(io);
    if( !qtIo->cpp_class )
        return NULL; // FIXME

    qtIo->cpp_class->addWatch( socket,
        events,
        func,
        user_data,
        notify );
    return NULL; // FIXME
}

static void qinf_qt_io_io_update_watch( InfIo *io,
    InfIoWatch* watch,
    InfIoEvent events )
{
    // FIXME
}

static void qinf_qt_io_io_remove_watch( InfIo *io,
    InfIoWatch* watch )
{
    // FIXME
}

static InfIoTimeout *qinf_qt_io_io_add_timeout( InfIo *io,
    guint msecs,
    InfIoTimeoutFunc func,
    void *user_data,
    GDestroyNotify notify )
{
    InfIoTimeout* timeout;
    QInfQtIo *qtIo;

    qtIo = QINF_QT_IO(io);
    if( !qtIo->cpp_class )
        return NULL;

    return qtIo->cpp_class->addTimeout( msecs,
        func,
        user_data,
        notify );
}

static void qinf_qt_io_io_remove_timeout( InfIo *io,
    InfIoTimeout *timer )
{
    QInfQtIo *qtIo;

    qtIo = QINF_QT_IO(io);
    if( !qtIo->cpp_class )
        return;

    qtIo->cpp_class->removeTimeout( timer );
}

static InfIoDispatch *qinf_qt_io_io_add_dispatch( InfIo *io,
    InfIoDispatchFunc func,
    gpointer user_data,
    GDestroyNotify notify )
{
    return NULL; // FIXME
}

static void qinf_qt_io_io_remove_dispatch( InfIo* io,
    InfIoDispatch* dispatch )
{
    // FIXME
}

static void qinf_qt_io_finalize( GObject *object )
{
    QInfQtIo *io;

    io = QINF_QT_IO(object);
    if( io->destroy_cpp_class && io->cpp_class )
    {
        io->cpp_class->setOwner( false );
        delete io->cpp_class;
    }

    G_OBJECT_CLASS(parent_class)->finalize(object);
}

static void qinf_qt_io_init( GTypeInstance *instance,
    gpointer g_class )
{
    GObjectClass *object_class;
    object_class = G_OBJECT_CLASS(g_class);
    QInfQtIo *io;
    parent_class = G_OBJECT_CLASS(g_type_class_peek_parent(g_class));
    io = (QInfQtIo*)instance;
    io->cpp_class = 0;
    io->destroy_cpp_class = 1;
    object_class->finalize = qinf_qt_io_finalize;
}

static void qinf_qt_io_class_init( gpointer g_class,
    gpointer class_data )
{
    GObjectClass *object_class;
    object_class = G_OBJECT_CLASS(g_class);
    object_class->finalize = qinf_qt_io_finalize;
}

static void qinf_qt_io_io_init( gpointer g_iface,
    gpointer iface_data )
{
    InfIoIface *iface;
    iface = (InfIoIface*)g_iface;

    iface->add_watch = qinf_qt_io_io_add_watch;
    iface->update_watch = qinf_qt_io_io_update_watch;
    iface->remove_watch = qinf_qt_io_io_remove_watch;

    iface->add_timeout = qinf_qt_io_io_add_timeout;
    iface->remove_timeout = qinf_qt_io_io_remove_timeout;

    iface->add_dispatch = qinf_qt_io_io_add_dispatch;
    iface->remove_dispatch = qinf_qt_io_io_remove_dispatch;
}

GType qinf_qt_io_get_type()
{
    static GType qt_io_type = 0;

    if( !qt_io_type )
    {
        static const GTypeInfo qt_io_type_info = {
            sizeof(QInfQtIoClass),
            NULL,
            NULL,
            qinf_qt_io_class_init,
            NULL,
            NULL,
            sizeof(QInfQtIo),
            -1,
            qinf_qt_io_init,
            NULL
        };

        static const GInterfaceInfo io_info = {
            qinf_qt_io_io_init,
            NULL,
            NULL
        };

        qt_io_type = g_type_register_static(
            G_TYPE_OBJECT,
            "QInfQtIo",
            &qt_io_type_info,
            (GTypeFlags)0
        );

        g_type_add_interface_static(
            qt_io_type,
            INF_TYPE_IO,
            &io_info
        );
    }

    return qt_io_type;
}

QInfQtIo *qinf_qt_io_new()
{
    GObject *object;
    object = G_OBJECT(g_object_new(QINF_TYPE_QT_IO, NULL));
    return QINF_QT_IO(object);
}

QtIo *QtIo::instance()
{
    static QtIo io;
    return &io;
}

QtIo::QtIo( QObject *parent )
    : QObject( parent )
    , m_gobject( qinf_qt_io_new() )
    , own_gobject( true )
{
    m_gobject->cpp_class = this;
}

QtIo::~QtIo()
{
    QList<QtIoWatch*> watches;
    QList<QtIoWatch*>::Iterator watchItr;

    watches = socketToWatchMap.values();
    for( watchItr = watches.begin(); watchItr != watches.end(); watchItr++ )
        delete *watchItr;

    m_gobject->destroy_cpp_class = 0;
    if( own_gobject )
        g_object_unref( m_gobject );
}

InfIoWatch *QtIo::addWatch( InfNativeSocket *socket,
    InfIoEvent events,
    InfIoWatchFunc func,
    gpointer user_data,
    GDestroyNotify notify )
{
    QtIoWatch *watch;

    if( socketToWatchMap.contains(*socket) )
    {
        socketToWatchMap[*socket]->deleteLater();
    }
    watch = new QtIoWatch( *socket,
        events,
        func,
        user_data,
        notify,
        this );
    socketToWatchMap[*socket] = watch;
}

void QtIo::updateWatch( InfIoWatch *watch,
    InfIoEvent events )
{
    // FIXME
}

void QtIo::removeWatch( InfIoWatch *watch )
{
    // FIXME
}

InfIoTimeout *QtIo::addTimeout( unsigned int msecs,
    InfIoTimeoutFunc func,
    void *user_data,
    GDestroyNotify notify )
{
    InfTimer *timer = new InfTimer( msecs, func,
        user_data, notify, this );
    timer->activate();
    return reinterpret_cast<InfIoTimeout*>(timer);
}

void QtIo::removeTimeout( InfIoTimeout *timer )
{
    InfTimer *t = reinterpret_cast<InfTimer*>(timer);
    delete t;
}

InfIoDispatch *QtIo::addDispatch( InfIoDispatchFunc func,
    gpointer user_data,
    GDestroyNotify notify )
{
    // FIXME
}

void QtIo::removeDispatch( InfIoDispatch *dispatch )
{
    // FIXME
}

GObject *QtIo::gobject() const
{
    return (GObject*)m_gobject;
}

void QtIo::setOwner( bool own_gobject )
{
    own_gobject = true;
}

InfTimer::InfTimer( unsigned int msecs,
    InfIoTimeoutFunc func,
    void *user_data,
    GDestroyNotify notify,
    QObject *parent )
    : QTimer( parent )
    , m_func( func )
    , m_user_data( user_data )
    , m_notify( notify )
{
    setInterval( msecs );
    setSingleShot( true );
}

InfTimer::~InfTimer()
{
    if( m_notify )
        m_notify( m_user_data );
}

void InfTimer::activate()
{
    connect( this, SIGNAL(timeout()),
        this, SLOT(activated()) );
    start();
}

void InfTimer::activated()
{
    m_func( m_user_data );
}

}

