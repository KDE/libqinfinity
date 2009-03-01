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
        bool isDirectory();
        void activate();

    private:
        BrowserIter m_iter;

};

/**
 * @brief Convenience QStandardItem class for representing an XmlConneciton.
 *
 * This class does not take ownership of any of its members.
 */
class ConnectionItem
    : public QStandardItem
    , public QObject
{

    public:
        ConnectionItem( XmlConnection &connection,
            Browser &browser,
            const QString &text );
        ConnectionItem( XmlConnection &connection,
            Browser &browser,
            const QIcon &icon,
            const QString &text );

        XmlConnection &connection() const;
        Browser &browser() const;
        int type() const;

    private:
        XmlConnection *m_connection;
        Browser *m_browser;
        
};

/**
 * @brief Handles creation of new file items
 */
class BrowserItemFactory
    : public QObject
{

    public:
        enum ItemType
        {
            NodeItem = 1001,
            ConnectionItem = 1002
        };

        /**
         * @brief Create an item factory.
         */
        BrowserItemFactory( QObject *parent = 0);
        virtual ~BrowserItemFactory();

        /**
         * @brief Create a new root node item.
         */
        virtual QInfinity::NodeItem *createRootNodeItem( const BrowserIter &node );

        /**
         * @brief Create a new node item.
         */
        virtual QInfinity::NodeItem *createNodeItem( const BrowserIter &node );

        /**
         * @brief Create a new connection item.
         */
        virtual QInfinity::ConnectionItem *createConnectionItem( XmlConnection &connection,
            Browser &browser,
            const QString &name );

};

}

#endif

