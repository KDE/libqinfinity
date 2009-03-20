#include "usertable.h"
#include "wrapperstore.h"

#include "usertable.moc"

namespace QInfinity
{

void user_cb( InfUser *user, void *user_data )
{
    QList<QPointer<User> > *userlist = static_cast<QList<QPointer<User> >* >(user_data);
    userlist->append( User::wrap( user ) );
}

QPointer<UserTable> UserTable::wrap( InfUserTable *infObject,
    QObject *parent,
    bool own_gobject )
{
    QGObject *wrapptr = WrapperStore::getWrapper( G_OBJECT(infObject), own_gobject );
    if( wrapptr)
        return dynamic_cast<UserTable*>(wrapptr);
    UserTable *wrapper = new UserTable( infObject, parent, own_gobject );
    WrapperStore::insertWrapper( G_OBJECT(infObject), wrapper );
    return wrapper;
}

UserTable::UserTable( QObject *parent )
    : QGObject( G_OBJECT(inf_user_table_new()), parent, true )
{
    setupSignals();
}

QPointer<User> UserTable::lookupUser( unsigned int id )
{
    InfUser *user = inf_user_table_lookup_user_by_id( INF_USER_TABLE(gobject()),
        id );
    if( user )
        return User::wrap( user, this );
    else
        return 0;
}

QPointer<User> UserTable::lookupUser( const QString &name )
{
    InfUser *user = inf_user_table_lookup_user_by_name( INF_USER_TABLE(gobject()),
        name.toAscii() );
    if( user )
        return User::wrap( user, this );
    else
        return 0;
}

QList<QPointer<User> > UserTable::localUsers()
{
    QList<QPointer<User> > userList;
    inf_user_table_foreach_local_user( INF_USER_TABLE(gobject()),
        user_cb, &userList );
    return userList;
}

QList<QPointer<User> > UserTable::users()
{
    QList<QPointer<User> > userList;
    inf_user_table_foreach_user( INF_USER_TABLE(gobject()),
        user_cb, &userList );
    return userList;
}

UserTable::UserTable( InfUserTable *infUserTable,
    QObject *parent,
    bool own_gobject )
    : QGObject( G_OBJECT(infUserTable), parent, own_gobject )
{
    setupSignals();
}

void UserTable::addLocalUserCb( InfUserTable *infUserTable,
    InfUser *infUser,
    void *user_data )
{
    UserTable *table = static_cast<UserTable*>(user_data);
    table->emitLocalUserAdded( User::wrap( infUser, table ) );
}

void UserTable::removeLocalUserCb( InfUserTable *infUserTable,
    InfUser *infUser,
    void *user_data )
{
    UserTable *table = static_cast<UserTable*>(user_data);
    table->emitLocalUserRemoved( User::wrap( infUser, table ) );
}

void UserTable::addUserCb( InfUserTable *infUserTable,
    InfUser *infUser,
    void *user_data )
{
    UserTable *table = static_cast<UserTable*>(user_data);
    table->emitUserAdded( User::wrap( infUser, table ) );
}

void UserTable::removeUserCb( InfUserTable *infUserTable,
    InfUser *infUser,
    void *user_data )
{
    UserTable *table = static_cast<UserTable*>(user_data);
    table->emitUserRemoved( User::wrap( infUser, table ) );
}

void UserTable::emitLocalUserAdded( User *user )
{
    emit( localUserAdded( user ) );
}

void UserTable::emitLocalUserRemoved( User *user )
{
    emit( localUserRemoved( user ) );
}

void UserTable::emitUserAdded( User *user )
{
    emit( userAdded( user ) );
}

void UserTable::emitUserRemoved( User *user )
{
    emit( userRemoved( user ) );
}

void UserTable::setupSignals()
{
    g_signal_connect( gobject(), "add-local-user",
        G_CALLBACK(UserTable::addLocalUserCb), this );
    g_signal_connect( gobject(), "remove-local-user",
        G_CALLBACK(UserTable::removeLocalUserCb), this );
    g_signal_connect( gobject(), "add-user",
        G_CALLBACK(UserTable::addUserCb), this );
    g_signal_connect( gobject(), "remove-user",
        G_CALLBACK(UserTable::removeUserCb), this );
}

}

