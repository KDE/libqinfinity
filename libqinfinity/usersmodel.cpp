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

#include "usersmodel.h"
#include "session.h"
#include "user.h"
#include "usertable.h"

#include <QPointer>
#include <QList>

#include "usersmodel.moc"

namespace QInfinity
{

class UserItemData
{

    public:
        QPointer<User> user;

};

class UsersModelData
{

    public:
        UserItemFactory *factory;
        QPointer<UserTable> userTable;
        QHash<User*, UserItem*> userToItem;

};

UserItem::UserItem( User &user )
    : QStandardItem( user.name() )
    , d( new UserItemData() )
{
    d->user = &user;
}

UserItemFactory::UserItemFactory()
{
}

UserItem *UserItemFactory::createUserItem( QInfinity::User &user )
{
    return new UserItem( user );
}

UsersModel::UsersModel( Session &session,
    QObject *parent )
    : d( new UsersModelData() )
{
    d->factory = new UserItemFactory();
    d->userTable = session.userTable();

    QList< QPointer<User> > userList = d->userTable->users();
    QPointer<User> user;
    foreach( user, userList )
    {
        if( user )
            insertUser( user );
    }

    connect( d->userTable.data(), SIGNAL(userAdded(User*)),
        this, SLOT(insertUser(User*)) );
    connect( d->userTable.data(), SIGNAL(userRemoved(User*)),
        this, SLOT(removeUser(User*)) );
}

void UsersModel::setFactory( UserItemFactory *factory )
{
    if( d->factory != factory )
        delete d->factory;
    

    if( !factory )
            d->factory = new UserItemFactory();
    else
        d->factory = factory;
}

void UsersModel::insertUser( User *user )
{
    if( user )
    {
        UserItem *item = new UserItem( *user );
        d->userToItem[user] = item;
        appendRow( item );
    }
}

void UsersModel::removeUser( User *user )
{
    if( user && d->userToItem.contains( user ) )
    {
        UserItem *item = d->userToItem[user];
        d->userToItem.remove( user );
        removeRow( item->row() );
    }
}

}

