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

        XmlConnection* connection() const;
        Browser* browser() const;
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

