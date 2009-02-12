#ifndef QINFINITY_FILE_ITEM_FACTORY
#define QINFINITY_FILE_ITEM_FACTORY

#include <QObject>
#include <QIcon>
#include <QStandardItem>

#include "browseriter.h"

namespace QInfinity
{

class XmlConnection;

/**
 * @brief Convinience QStandardItem class for representing a BrowserIter
 */
class NodeItem
    : public QStandardItem
{

    public:
        /**
         * @brief Create item with iter.name() as text.
         */
        NodeItem( const BrowserIter &iter );
        NodeItem( const BrowserIter &iter,
            const QString &text );
        NodeItem( const BrowserIter &iter,
            const QIcon &icon );
        NodeItem( const BrowserIter &iter,
            const QIcon &icon,
            const QString &text );

        const BrowserIter &iter() const;
        int type() const;

    private:
        BrowserIter m_iter;

};

/**
 * @brief Convenience QStandardItem class for representing an XmlConneciton.
 */
class ConnectionItem
    : public QStandardItem
{

    public:
        ConnectionItem( XmlConnection &connection,
            const QString &text );
        ConnectionItem( XmlConnection &connection,
            const QIcon &icon,
            const QString &text );

        XmlConnection &connection() const;
        int type() const;

    private:
        XmlConnection *m_connection;
        
};

/**
 * @brief Handles creation of new file items
 */
class FileItemFactory
    : public QObject
{

    public:
        enum ItemType
        {
            NodeItem = 1001,
            ConnectionItem = 1002
        };

        FileItemFactory( QObject *parent = 0);
        virtual ~FileItemFactory();

        /**
         * @brief Create a new node item.
         *
         * Use the BrowserIter interface to distinguish node types.
         */
        virtual QInfinity::NodeItem *createRootNodeItem( const BrowserIter &node );
        virtual QInfinity::NodeItem *createNodeItem( const BrowserIter &node );
        virtual QInfinity::ConnectionItem *createConnectionItem( XmlConnection &connection,
            const QString &name );

};

}

#endif

