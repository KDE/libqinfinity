#include "browseriter.h"
#include "browser.h"

namespace QInfinity
{

BrowserIter::BrowserIter( const Browser &browser )
    : m_infBrowser( INFC_BROWSER(browser.gobject()) )
{
    infc_browser_iter_get_root( m_infBrowser, &m_infBrowserIter );
}

BrowserIter::BrowserIter( const InfcBrowserIter *infIter,
    InfcBrowser *infBrowser )
    : m_infBrowser( infBrowser )
{
    m_infBrowserIter.node_id = infIter->node_id;
    m_infBrowserIter.node = infIter->node;
}

BrowserIter::BrowserIter( const BrowserIter &other )
    : m_infBrowser( other.infBrowser() )
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

BrowserIter &BrowserIter::operator=( const BrowserIter &other )
{
    m_infBrowser = other.infBrowser();
    m_infBrowserIter.node_id = other.infBrowserIter()->node_id;
    m_infBrowserIter.node = other.infBrowserIter()->node;
}

bool BrowserIter::next()
{
    if( m_infBrowser )
        return infc_browser_iter_get_next( m_infBrowser, &m_infBrowserIter ) != 0;
}

bool BrowserIter::prev()
{
    if( m_infBrowser )
        return infc_browser_iter_get_prev( m_infBrowser, &m_infBrowserIter ) != 0;
}

bool BrowserIter::child()
{
    if( m_infBrowser )
        return infc_browser_iter_get_child( m_infBrowser, &m_infBrowserIter ) != 0;
}

bool BrowserIter::parent()
{
    if( m_infBrowser )
        return infc_browser_iter_get_parent( m_infBrowser, &m_infBrowserIter ) != 0;
}

bool BrowserIter::isDirectory()
{
    if( m_infBrowser )
        return infc_browser_iter_is_subdirectory( m_infBrowser, &m_infBrowserIter ) != 0;
}

InfcExploreRequest *BrowserIter::explore()
{
    if( m_infBrowser )
        return infc_browser_iter_explore( m_infBrowser, &m_infBrowserIter );
}

bool BrowserIter::isExplored()
{
    if( m_infBrowser )
        return infc_browser_iter_get_explored( m_infBrowser, &m_infBrowserIter ) != 0;
}

const char *BrowserIter::name()
{
    if( m_infBrowser )
        return infc_browser_iter_get_name( m_infBrowser, &m_infBrowserIter );
}

const char *BrowserIter::path()
{
    if( m_infBrowser )
        return infc_browser_iter_get_path( m_infBrowser, &m_infBrowserIter );
}

Browser *BrowserIter::browser() const
{
    return Browser::create( infBrowser() );
}

InfcBrowser *BrowserIter::infBrowser() const
{
    if( m_infBrowser )
        return m_infBrowser;
}

const InfcBrowserIter *BrowserIter::infBrowserIter() const
{
    if( m_infBrowser )
        return &m_infBrowserIter;
}

InfcBrowserIter *BrowserIter::infBrowserIter()
{
    if( m_infBrowser )
        return &m_infBrowserIter;
}

}

