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

#include "browser.h"
#include "noteplugin.h"
#include "sessionproxy.h"
#include "session.h"
#include "xmlconnection.h"
#include "qtio.h"
#include "communicationmanager.h"
#include "wrapperstore.h"
#include "qgsignal.h"
#include "noderequest.h"

#include <libinfinity/common/inf-buffer.h>
#include <libinfinity/client/infc-browser.h>
#include <libinfinity/client/infc-explore-request.h>
#include <libinfinity/client/infc-node-request.h>

#include <QDebug>

#include <glib-object.h>

#include "browser.moc"

namespace QInfinity
{

QPointer<Browser> Browser::wrap( InfcBrowser *infObject,
    QObject *parent,
    bool own_gobject )
{
    QGObject *wrapptr = WrapperStore::getWrapper( G_OBJECT(infObject), own_gobject );
    if( wrapptr)
        return dynamic_cast<Browser*>(wrapptr);
    Browser *wrapper = new Browser( infObject, parent, own_gobject );
    return wrapper;
}

Browser::Browser( CommunicationManager& comm_manager,
    XmlConnection* connection,
    QObject *parent )
    : QGObject( (GObject*)infc_browser_new( INF_IO(QtIo::instance()->gobject()),
            INF_COMMUNICATION_MANAGER(comm_manager.gobject()),
            INF_XML_CONNECTION(connection->gobject()) ),
        parent )
{
    setupSignals();
}

bool Browser::addPlugin( NotePlugin &plugin )
{
    return infc_browser_add_plugin( INFC_BROWSER(this->gobject()),
        plugin.infPlugin() ) != 0;
}

NodeRequest *Browser::addSubdirectory( BrowserIter parent,
    const char *name )
{
    return NodeRequest::wrap(inf_browser_add_subdirectory( INF_BROWSER(this->gobject()),
        parent.infBrowserIter(), name, 0 ));
}

NodeRequest *Browser::addNote( BrowserIter parent,
    const char *name,
    NotePlugin &plugin,
    bool initial_subscribe )
{
    return NodeRequest::wrap(inf_browser_add_note( INF_BROWSER(this->gobject()),
        parent.infBrowserIter(), name,
        plugin.infPlugin()->note_type, 0, 0,
        initial_subscribe ));
}

NodeRequest *Browser::addNoteWithContent( BrowserIter parent,
    const char *name,
    NotePlugin &plugin,
    Session &session,
    bool initial_subscribe )
{
    return NodeRequest::wrap(inf_browser_add_note(INF_BROWSER(this->gobject()),
        parent.infBrowserIter(), name,
        plugin.infPlugin()->note_type, 0, INF_SESSION(session.gobject()),
        initial_subscribe));
}

NodeRequest *Browser::removeNode( BrowserIter node )
{
    return NodeRequest::wrap(inf_browser_remove_node( INF_BROWSER(this->gobject()),
        node.infBrowserIter() ));
}

NodeRequest *Browser::subscribeSession( BrowserIter node, NotePlugin* plugin, QInfinity::AbstractTextBuffer* textBuffer )
{
    return NodeRequest::wrap(inf_browser_subscribe( INF_BROWSER(this->gobject()), node.infBrowserIter() ));
}

Browser::Browser( InfcBrowser *browser,
    QObject *parent,
    bool own_gobject )
    : QGObject( G_OBJECT(browser), parent, own_gobject )
{
    setupSignals();
}

InfBrowserStatus Browser::connectionStatus() const
{
    InfBrowserStatus status;
    g_object_get(G_OBJECT(gobject()), "status", &status, NULL);
    return status;
}

XmlConnection* Browser::connection() const
{
    return XmlConnection::wrap(infc_browser_get_connection(INFC_BROWSER(gobject())));
}

void Browser::setupSignals()
{
    new QGSignal( this, "begin-request::explore",
        G_CALLBACK(Browser::begin_explore_cb), this, this );
    new QGSignal( this, "begin-request::subscribe",
        G_CALLBACK(Browser::begin_subscribe_cb), this, this );
    new QGSignal( this, "subscribe-session",
        G_CALLBACK(Browser::subscribe_session_cb), this, this );
    new QGSignal( this, "node-added", 
        G_CALLBACK(Browser::node_added_cb), this, this );
    new QGSignal( this, "node-removed", 
        G_CALLBACK(Browser::node_removed_cb), this, this );
    new QGSignal( this, "error",
        G_CALLBACK(Browser::error_cb), this, this );
    qDebug() << "connecting browser instance" << this;
    g_signal_connect_data(INFC_BROWSER(gobject()), "notify",
                           G_CALLBACK(Browser::status_changed_cb), 0, NULL, G_CONNECT_AFTER );
}

// GObject signals

void Browser::signalBeginExplore( InfBrowserIter *infIter,
    InfcExploreRequest *request )
{
    BrowserIter iter( infIter, INFC_BROWSER(this->gobject()) );
    emit(beginExplore( iter, request ));
}

void Browser::signalBeginSubscribe( InfBrowserIter *infIter,
    InfcNodeRequest *request )
{
    BrowserIter iter( infIter, INFC_BROWSER(this->gobject()) );
    emit(beginSubscribe( iter, request ));
}

void Browser::signalSubscribeSession( InfBrowserIter *infIter,
    InfcSessionProxy *infProxy )
{
    BrowserIter iter( infIter, INFC_BROWSER(this->gobject()) );
    emit(subscribeSession( iter,
        SessionProxy::wrap( infProxy, this ) ));
}

void Browser::signalNodeAdded( InfBrowserIter *infIter )
{
    BrowserIter iter( infIter, INFC_BROWSER(this->gobject()) );
    emit(nodeAdded( iter ));
}

void Browser::signalNodeRemoved( InfBrowserIter *infIter )
{
    BrowserIter iter( infIter, INFC_BROWSER(this->gobject()) );
    emit(nodeRemoved( iter ));
}

void Browser::signalError(const QString message)
{
    qDebug() << "browser error:" << message;
    emit(error( this, message ));
}

void Browser::signalStatusChanged(InfBrowserStatus status)
{
    qDebug() << "status changed to" << status << "(connected:" << INF_BROWSER_OPEN << ")" << "on" << this;
    if ( status == INF_BROWSER_OPEN ) {
        qDebug() << "emitting connection established for browser" << this;
        emit(connectionEstablished( this ));
    }
}

void Browser::status_changed_cb(InfcBrowser* browser, void* user_data)
{
    qDebug() << "got status changed callback";
    QPointer<Browser> qbrowser = wrap(browser);
    qbrowser->signalStatusChanged( qbrowser->connectionStatus() );
}

void Browser::begin_explore_cb( InfcBrowser *browser,
    InfBrowserIter *iter,
    InfcExploreRequest *request,
    void *user_data )
{
    static_cast<Browser*>(user_data)->signalBeginExplore( iter, request );
}

void Browser::begin_subscribe_cb( InfcBrowser *browser,
    InfBrowserIter *iter,
    InfcNodeRequest *request,
    void *user_data )
{
    static_cast<Browser*>(user_data)->signalBeginSubscribe( iter, request );
}

void Browser::subscribe_session_cb( InfcBrowser *browser,
    InfBrowserIter *iter,
    InfcSessionProxy *proxy,
    void *user_data )
{
    static_cast<Browser*>(user_data)->signalSubscribeSession( iter, proxy );
}

void Browser::error_cb( InfcBrowser* browser,
    const GError* gerror )
{
    QString message(gerror->message);
    QPointer<Browser> qbrowser = wrap(browser);
    qbrowser->signalError(message);
}

void Browser::node_added_cb( InfcBrowser *browser,
    InfBrowserIter *iter,
    void *user_data )
{
    static_cast<Browser*>(user_data)->signalNodeAdded( iter );
}

void Browser::node_removed_cb( InfcBrowser *browser,
    InfBrowserIter *iter,
    void *user_data )
{
    static_cast<Browser*>(user_data)->signalNodeRemoved( iter );
}

}

