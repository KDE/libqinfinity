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

#ifndef QINFINITY_USERSMODEL_H
#define QINFINITY_USERSMODEL_H

#include <QStandardItemModel>
#include <QStandardItem>
#include <QHash>

namespace QInfinity
{

class Session;
class User;
class UserItemData;
class UsersModelData;

class UserItem
    : public QStandardItem
{

    public:
        UserItem( User &user );

    private:
        UserItemData *d;

};

class UserItemFactory
{

    public:
        UserItemFactory();
        virtual ~UserItemFactory() { }

        virtual UserItem *createUserItem( QInfinity::User &user );

};

class UsersModel
    : public QStandardItemModel
{
    Q_OBJECT

    public:
        /**
         * @brief Create model of users in session.
         */
        UsersModel( Session &session, UserItemFactory *factory = 0, QObject *parent = 0 );

        /**
         * @brief Set factory to create user items.
         *
         * The current item factory is deleted before the new
         * one is set.
         */
        void setFactory( UserItemFactory *factory );
    
    private Q_SLOTS:
        void insertUser( User *user );
        void removeUser( User *user );

    private:
        UsersModelData *d;

};

}

#endif

