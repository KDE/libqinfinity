#include "user.h"
#include "wrapperstore.h"

namespace QInfinity
{

User *User::create( InfUser *infUser,
    QObject *parent )
{
    WrapperStore *store = WrapperStore::instance();
    User *user = dynamic_cast<User*>(store->findWrapper( G_OBJECT(infUser) ));
    if( !user )
        user = new User( infUser, parent );
    return user;
}

unsigned int User::id()
{
    return inf_user_get_id( INF_USER(gobject()) );
}

QString User::name()
{
    return inf_user_get_name( INF_USER(gobject()) );
}

User::Status User::status()
{
    return User::convertStatus( inf_user_get_status( INF_USER(gobject()) ) );
}

User::Status User::convertStatus( InfUserStatus status )
{
    Status ret;
    switch( status )
    {
        case INF_USER_ACTIVE:
            ret = Active;
            break;
        case INF_USER_INACTIVE:
            ret = Inactive;
            break;
        case INF_USER_UNAVAILABLE:
            ret = Unavailable;
    }
    return ret;
}

InfUserStatus User::convertStatus( Status status )
{
    InfUserStatus ret;
    switch( status )
    {
        case Active:
            ret = INF_USER_ACTIVE;
            break;
        case Inactive:
            ret = INF_USER_INACTIVE;
            break;
        case Unavailable:
            ret = INF_USER_UNAVAILABLE;
    }
    return ret;
}

User::User( InfUser *infUser,
    QObject *parent )
    : QGObject( G_OBJECT(infUser) )
{
}

}

