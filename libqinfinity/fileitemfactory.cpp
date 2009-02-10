#include "fileitemfactory.h"
#include "browseriter.h"
#include "xmlconnection.h"

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
    return FileItemFactory::NodeItem;
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
    return FileItemFactory::ConnectionItem;
}

FileItemFactory::FileItemFactory( QObject *parent )
    : QObject( parent )
{
}

FileItemFactory::~FileItemFactory()
{
}

NodeItem *FileItemFactory::createNodeItem( const BrowserIter &node )
{
    QInfinity::NodeItem *item = new QInfinity::NodeItem( node );
    return item;
}

ConnectionItem *FileItemFactory::createConnectionItem( XmlConnection &connection,
    const QString &name )
{
    QInfinity::ConnectionItem *item = new QInfinity::ConnectionItem( connection, name );
    return item;
}

}

