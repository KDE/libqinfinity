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

#include <libinfinity/common/inf-buffer.h>
#include <libinfinity/client/infc-browser.h>
#include <libinfinity/client/infc-explore-request.h>
#include <libinfinity/client/infc-node-request.h>

#include <QDebug>

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

Browser::Browser( CommunicationManager &comm_manager,
    XmlConnection &connection,
    QObject *parent )
    : QGObject( (GObject*)infc_browser_new( INF_IO(QtIo::instance()->gobject()),
            INF_COMMUNICATION_MANAGER(comm_manager.gobject()),
            INF_XML_CONNECTION(connection.gobject()) ),
        parent )
{
    setupSignals();
}

bool Browser::addPlugin( NotePlugin &plugin )
{
    return infc_browser_add_plugin( INFC_BROWSER(this->gobject()),
        plugin.infPlugin() ) != 0;
}

InfcNodeRequest *Browser::addSubdirectory( BrowserIter parent,
    const char *name )
{
    return infc_browser_add_subdirectory( INFC_BROWSER(this->gobject()),
        parent.infBrowserIter(), name );
}

InfcNodeRequest *Browser::addNote( BrowserIter parent,
    const char *name,
    NotePlugin &plugin,
    bool initial_subscribe )
{
    return infc_browser_add_note( INFC_BROWSER(this->gobject()),
        parent.infBrowserIter(), name,
        plugin.infPlugin(),
        initial_subscribe );
}

InfcNodeRequest *Browser::addNoteWithContent( BrowserIter parent,
    const char *name,
    NotePlugin &plugin,
    Session &session,
    bool initial_subscribe )
{
    return infc_browser_add_note_with_content(INFC_BROWSER(this->gobject()),
        parent.infBrowserIter(), name,
        plugin.infPlugin(), INF_SESSION(session.gobject()),
        initial_subscribe);
}

InfcNodeRequest *Browser::removeNode( BrowserIter node )
{
    return infc_browser_remove_node( INFC_BROWSER(this->gobject()),
        node.infBrowserIter() );
}

InfcNodeRequest *Browser::subscribeSession( BrowserIter node )
{
    return infc_browser_iter_subscribe_session( INFC_BROWSER(this->gobject()),
        node.infBrowserIter() );
}

Browser::Browser( InfcBrowser *browser,
    QObject *parent,
    bool own_gobject )
    : QGObject( G_OBJECT(browser), parent, own_gobject )
{
    setupSignals();
}

void Browser::setupSignals()
{
    g_signal_connect( G_OBJECT(this->gobject()),
        "begin-explore", G_CALLBACK(Browser::begin_explore_cb),
        this );
    g_signal_connect( G_OBJECT(this->gobject()),
        "begin-subscribe", G_CALLBACK(Browser::begin_subscribe_cb),
        this );
    g_signal_connect( G_OBJECT(this->gobject()),
        "subscribe-session", G_CALLBACK(Browser::subscribe_session_cb),
        this );
    g_signal_connect( G_OBJECT(this->gobject()),
        "node-added", G_CALLBACK(Browser::node_added_cb),
        this );
    g_signal_connect( G_OBJECT(this->gobject()),
        "node-removed", G_CALLBACK(Browser::node_removed_cb),
        this );
}

// GObject signals

void Browser::signalBeginExplore( InfcBrowserIter *infIter,
    InfcExploreRequest *request )
{
    BrowserIter iter( infIter, INFC_BROWSER(this->gobject()) );
    emit(beginExplore( iter, request ));
}

void Browser::signalBeginSubscribe( InfcBrowserIter *infIter,
    InfcNodeRequest *request )
{
    BrowserIter iter( infIter, INFC_BROWSER(this->gobject()) );
    emit(beginSubscribe( iter, request ));
}

void Browser::signalSubscribeSession( InfcBrowserIter *infIter,
    InfcSessionProxy *infProxy )
{
    BrowserIter iter( infIter, INFC_BROWSER(this->gobject()) );
    emit(subscribeSession( iter,
        SessionProxy::wrap( infProxy, this ) ));
}

void Browser::signalNodeAdded( InfcBrowserIter *infIter )
{
    BrowserIter iter( infIter, INFC_BROWSER(this->gobject()) );
    emit(nodeAdded( iter ));
}

void Browser::signalNodeRemoved( InfcBrowserIter *infIter )
{
    BrowserIter iter( infIter, INFC_BROWSER(this->gobject()) );
    emit(nodeRemoved( iter ));
}

void Browser::begin_explore_cb( InfcBrowser *browser,
    InfcBrowserIter *iter,
    InfcExploreRequest *request,
    void *user_data )
{
    static_cast<Browser*>(user_data)->signalBeginExplore( iter, request );
}

void Browser::begin_subscribe_cb( InfcBrowser *browser,
    InfcBrowserIter *iter,
    InfcNodeRequest *request,
    void *user_data )
{
    static_cast<Browser*>(user_data)->signalBeginSubscribe( iter, request );
}

void Browser::subscribe_session_cb( InfcBrowser *browser,
    InfcBrowserIter *iter,
    InfcSessionProxy *proxy,
    void *user_data )
{
    static_cast<Browser*>(user_data)->signalSubscribeSession( iter, proxy );
}

void Browser::node_added_cb( InfcBrowser *browser,
    InfcBrowserIter *iter,
    void *user_data )
{
    static_cast<Browser*>(user_data)->signalNodeAdded( iter );
}

void Browser::node_removed_cb( InfcBrowser *browser,
    InfcBrowserIter *iter,
    void *user_data )
{
    static_cast<Browser*>(user_data)->signalNodeRemoved( iter );
}

}

