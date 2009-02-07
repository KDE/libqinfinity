#include "browser.h"
#include "xmlconnection.h"
#include "qtio.h"
#include "communicationmanager.h"
#include "browseriter.h"

#include <libinfinity/client/infc-browser.h>
#include <libinfinity/client/infc-explore-request.h>
#include <libinfinity/client/infc-node-request.h>

#include "browser.moc"

namespace QInfinity
{

Browser::Browser( QtIo &io,
    CommunicationManager &comm_manager,
    XmlConnection &connection,
    QObject *parent )
    : QObject( parent )
    , QGObject( (GObject*)infc_browser_new( (InfIo*)io.gobject(),
        (InfCommunicationManager*)comm_manager.gobject(),
        (InfXmlConnection*)connection.gobject() ) )
{
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
        "node-removed", G_CALLBACK(Browser::node_added_cb),
        this );
}

// GObject signals

void Browser::signalBeginExplore( InfcBrowserIter *infIter,
    InfcExploreRequest *request )
{
    BrowserIter iter( infIter, INFC_BROWSER(this->gobject()), this );
    emit(beginExplore( QPointer<BrowserIter>(&iter), request ));
}

void Browser::signalBeginSubscribe( InfcBrowserIter *infIter,
    InfcNodeRequest *request )
{
    BrowserIter iter( infIter, INFC_BROWSER(this->gobject()), this );
    emit(beginSubscribe( QPointer<BrowserIter>(&iter), request ));
}

void Browser::signalSubscribeSession( InfcBrowserIter *infIter,
    InfcSessionProxy *proxy )
{
    BrowserIter iter( infIter, INFC_BROWSER(this->gobject()), this );
    emit(subscribeSession( QPointer<BrowserIter>(&iter), proxy ));
}

void Browser::signalNodeAdded( InfcBrowserIter *infIter )
{
    BrowserIter iter( infIter, INFC_BROWSER(this->gobject()), this );
    emit(nodeAdded( QPointer<BrowserIter>(&iter) ));
}

void Browser::signalNodeRemoved( InfcBrowserIter *infIter )
{
    BrowserIter iter( infIter, INFC_BROWSER(this->gobject()), this );
    emit(nodeRemoved( QPointer<BrowserIter>(&iter) ));
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

