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
#include "user.h"

#include <QPointer>

#include "usersmodel.moc"

namespace QInfinity
{

class UserItemData
{

    public:
        QPointer<User> user;

};

UserItem::UserItem( User &user )
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

UsersModel::UsersModel( QObject *parent )
{
    m_factory = new UserItemFactory();
}

void UsersModel::setFactory( UserItemFactory *factory )
{
    if( factory != m_factory )
        delete m_factory;
    else
    {
        if( !factory )
            m_factory = new UserItemFactory();
        else
            m_factory = factory;
    }
}

}

