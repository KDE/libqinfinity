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

#include "browseriter.h"
#include "browser.h"
#include "explorerequest.h"

namespace QInfinity
{

BrowserIter::BrowserIter( const Browser &browser )
    : m_infBrowser( INFC_BROWSER(browser.gobject()) )
{
    Q_ASSERT(browser.connectionStatus() == INF_BROWSER_OPEN);
    inf_browser_get_root(INF_BROWSER(m_infBrowser), &m_infBrowserIter);
}

BrowserIter::BrowserIter( const InfBrowserIter *infIter,
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
    return *this;
}

bool BrowserIter::next()
{
    if( m_infBrowser )
        return inf_browser_get_next( INF_BROWSER(m_infBrowser), &m_infBrowserIter ) != 0;
    return 0;
}

bool BrowserIter::prev()
{
    if( m_infBrowser )
        return inf_browser_get_prev( INF_BROWSER(m_infBrowser), &m_infBrowserIter ) != 0;
    return 0;
}

bool BrowserIter::child()
{
    if( m_infBrowser )
        return inf_browser_get_child( INF_BROWSER(m_infBrowser), &m_infBrowserIter ) != 0;
    return 0;
}

bool BrowserIter::parent()
{
    if( m_infBrowser )
        return inf_browser_get_parent( INF_BROWSER(m_infBrowser), &m_infBrowserIter ) != 0;
    return 0;
}

bool BrowserIter::isDirectory()
{
    if( m_infBrowser )
        return inf_browser_is_subdirectory( INF_BROWSER(m_infBrowser), &m_infBrowserIter ) != 0;
    return 0;
}

ExploreRequest* BrowserIter::explore()
{
    if( m_infBrowser ) {
        InfExploreRequest* req = INF_EXPLORE_REQUEST( inf_browser_get_pending_request(
            INF_BROWSER(m_infBrowser),
            &m_infBrowserIter,
            "explore-node" )
        );
        if ( req ) {
            return ExploreRequest::wrap(req, 0, false);
        }
        else {
            return ExploreRequest::wrap( INF_EXPLORE_REQUEST(inf_browser_explore(
                INF_BROWSER(m_infBrowser), &m_infBrowserIter
            )) );
        }
    }
    return 0;
}

ExploreRequest* BrowserIter::exploreRequest() const
{
    if( m_infBrowser ) {
        InfExploreRequest* req = INF_EXPLORE_REQUEST( inf_browser_get_pending_request(
            INF_BROWSER(m_infBrowser),
            &m_infBrowserIter,
            "explore-node" )
        );
        return ExploreRequest::wrap(req, 0, false);
    }
    return 0;
}

bool BrowserIter::isExplored()
{
    if( m_infBrowser )
        return inf_browser_get_explored( INF_BROWSER(m_infBrowser), &m_infBrowserIter ) != 0;
    return 0;
}

QString BrowserIter::name() const
{
    if( m_infBrowser )
        return inf_browser_get_node_name( INF_BROWSER(m_infBrowser), &m_infBrowserIter );
    return "";
}

QString BrowserIter::path() const
{
    if( m_infBrowser )
        return inf_browser_get_path( INF_BROWSER(m_infBrowser), &m_infBrowserIter );
    return "";
}

unsigned int BrowserIter::id() const
{
    return m_infBrowserIter.node_id;
}

QPointer<Browser> BrowserIter::browser() const
{
    return Browser::wrap( infBrowser() );
}

InfcBrowser *BrowserIter::infBrowser() const
{
    if( m_infBrowser )
        return m_infBrowser;
    return 0;
}

const InfBrowserIter *BrowserIter::infBrowserIter() const
{
    if( m_infBrowser )
        return &m_infBrowserIter;
    return 0;
}

InfBrowserIter *BrowserIter::infBrowserIter()
{
    if( m_infBrowser )
        return &m_infBrowserIter;
    return 0;
}

QString BrowserIter::noteType()
{
    if( m_infBrowser )
        return inf_browser_get_node_type( INF_BROWSER(m_infBrowser), &m_infBrowserIter );
    return "";
}

}

