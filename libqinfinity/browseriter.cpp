#include "browseriter.h"
#include "browser.h"

namespace QInfinity
{

BrowserIter::BrowserIter( const Browser &browser,
    QObject *parent )
    : QObject( parent )
    , m_infBrowser( INFC_BROWSER(browser.gobject()) )
{
    infc_browser_iter_get_root( m_infBrowser, &m_infBrowserIter );
}

BrowserIter::BrowserIter( const InfcBrowserIter *infIter,
    InfcBrowser *infBrowser,
    QObject *parent )
    : QObject( parent )
    , m_infBrowser( infBrowser )
{
    m_infBrowserIter.node_id = infIter->node_id;
    m_infBrowserIter.node = infIter->node;
}

BrowserIter::BrowserIter( const BrowserIter &other,
    QObject *parent )
    : QObject( parent )
    , m_infBrowser( other.infBrowser() )
{
    m_infBrowserIter.node_id = other.infBrowserIter()->node_id;
    m_infBrowserIter.node = other.infBrowserIter()->node;
}

BrowserIter &BrowserIter::operator++()
{
    next();
    return *this;
}

BrowserIter BrowserIter::operator++( int dummy )
{
    next();
    return *this;
}

BrowserIter &BrowserIter::operator--()
{
    prev();
    return *this;
}

BrowserIter BrowserIter::operator--( int dummy )
{
    prev();
    return *this;
}

bool BrowserIter::next()
{
    return infc_browser_iter_get_next( m_infBrowser, &m_infBrowserIter ) != 0;
}

bool BrowserIter::prev()
{
    return infc_browser_iter_get_prev( m_infBrowser, &m_infBrowserIter ) != 0;
}

bool BrowserIter::child()
{
    return infc_browser_iter_get_child( m_infBrowser, &m_infBrowserIter ) != 0;
}

bool BrowserIter::parent()
{
    return infc_browser_iter_get_parent( m_infBrowser, &m_infBrowserIter ) != 0;
}

InfcExploreRequest *BrowserIter::explore()
{
    return infc_browser_iter_explore( m_infBrowser, &m_infBrowserIter );
}

bool BrowserIter::isExplored()
{
    return infc_browser_iter_get_explored( m_infBrowser, &m_infBrowserIter ) != 0;
}

const char *BrowserIter::name()
{
    return infc_browser_iter_get_name( m_infBrowser, &m_infBrowserIter );
}

const char *BrowserIter::path()
{
    return infc_browser_iter_get_path( m_infBrowser, &m_infBrowserIter );
}

InfcBrowser *BrowserIter::infBrowser() const
{
    return m_infBrowser;
}

const InfcBrowserIter *BrowserIter::infBrowserIter() const
{
    return &m_infBrowserIter;
}

}

