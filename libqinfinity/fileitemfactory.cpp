#include "fileitemfactory.h"
#include "browseriter.h"

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

FileItemFactory::FileItemFactory( QObject *parent )
    : QObject( parent )
{
}

QStandardItem *FileItemFactory::newDirectoryItem( const BrowserIter &node )
{
    return new NodeItem( node );
}

QStandardItem *FileItemFactory::newNoteItem( const BrowserIter &node )
{
    return new NodeItem( node );
}

QStandardItem *FileItemFactory::newConnectionItem( XmlConnection &connection,
    const QString &name )
{
    return new ConnectionItem( connection, name );
}

}

