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
}

NodeItem::NodeItem( const BrowserIter &iter,
    const QString &text )
    : QStandardItem( text )
    , m_iter( iter )
{
}

NodeItem::NodeItem( const BrowserIter &iter,
    const QIcon &icon )
    : QStandardItem()
    , m_iter( iter )
{
    setText( m_iter.name() );
}

NodeItem::NodeItem( const BrowserIter &iter,
    const QIcon &icon,
    const QString &text )
    : QStandardItem( icon, text )
    , m_iter( iter )
{
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
    const QString &text )
    : QStandardItem( text )
    , m_connection( &connection )
{
}

ConnectionItem::ConnectionItem( XmlConnection &connection,
    const QIcon &icon,
    const QString &text )
    : QStandardItem( icon, text )
    , m_connection( &connection )
{
}

XmlConnection &ConnectionItem::connection() const
{
    return *m_connection;
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
    const QString &name )
{
    QInfinity::ConnectionItem *item = new QInfinity::ConnectionItem( connection, name );
    return item;
}

}

