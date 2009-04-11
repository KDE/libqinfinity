#include "browseritemfactory.h"
#include "browseriter.h"
#include "xmlconnection.h"

#include <QDebug>

namespace QInfinity
{

NodeItem::NodeItem( const BrowserIter &iter )
    : QStandardItem()
    , m_iter( iter )
{
    setText( m_iter.name() );
    setEditable( false );
}

NodeItem::NodeItem( const BrowserIter &iter,
    const QString &text )
    : QStandardItem( text )
    , m_iter( iter )
{
    setEditable( false );
}

NodeItem::NodeItem( const BrowserIter &iter,
    const QIcon &icon )
    : QStandardItem()
    , m_iter( iter )
{
    setIcon( icon );
    setText( m_iter.name() );
    setEditable( false );
}

NodeItem::NodeItem( const BrowserIter &iter,
    const QIcon &icon,
    const QString &text )
    : QStandardItem( icon, text )
    , m_iter( iter )
{
    setEditable( false );
}

const BrowserIter &NodeItem::iter() const
{
    return m_iter;
}

int NodeItem::type() const
{
    return BrowserItemFactory::NodeItem;
}

bool NodeItem::isDirectory()
{
    return m_iter.isDirectory();
}

void NodeItem::activate()
{
    if( !m_iter.isExplored() )
        m_iter.explore();
}

ConnectionItem::ConnectionItem( XmlConnection &connection,
    Browser &browser,
    const QString &text )
    : QStandardItem( text )
    , m_connection( &connection )
    , m_browser( &browser )
{
    setEditable( false );
}

ConnectionItem::ConnectionItem( XmlConnection &connection,
    Browser &browser,
    const QIcon &icon,
    const QString &text )
    : QStandardItem( icon, text )
    , m_connection( &connection )
    , m_browser( &browser )
{
    setEditable( false );
}

XmlConnection &ConnectionItem::connection() const
{
    return *m_connection;
}

Browser &ConnectionItem::browser() const
{
    return *m_browser;
}

int ConnectionItem::type() const
{
    return BrowserItemFactory::ConnectionItem;
}

BrowserItemFactory::BrowserItemFactory( QObject *parent )
    : QObject( parent )
{
}

BrowserItemFactory::~BrowserItemFactory()
{
}

NodeItem *BrowserItemFactory::createRootNodeItem( const BrowserIter &node )
{
    QInfinity::NodeItem *item = new QInfinity::NodeItem( node, "/" );
    return item;
}

NodeItem *BrowserItemFactory::createNodeItem( const BrowserIter &node )
{
    QInfinity::NodeItem *item = new QInfinity::NodeItem( node );
    return item;
}

ConnectionItem *BrowserItemFactory::createConnectionItem( XmlConnection &connection,
    Browser &browser,
    const QString &name )
{
    QInfinity::ConnectionItem *item = new QInfinity::ConnectionItem( connection,
        browser,
        name );
    return item;
}

}

