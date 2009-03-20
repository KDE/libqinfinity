#include "usertable.h"
#include "wrapperstore.h"

namespace QInfinity
{

QPointer<UserTable> UserTable::wrap( InfUserTable *infObject,
    QObject *parent,
    bool own_gobject )
{
    if( own_gobject )
        return new UserTable( infObject, parent, true );
    QGObject *wrapptr = WrapperStore::getWrapper( G_OBJECT(infObject) );
    if( wrapptr)
        return dynamic_cast<UserTable*>(wrapptr);
    UserTable *wrapper = new UserTable( infObject, parent, false );
    WrapperStore::insertWrapper( G_OBJECT(infObject), wrapper );
    return wrapper;
}

UserTable::UserTable( QObject *parent )
    : QGObject( G_OBJECT(inf_user_table_new()), parent, true )
{
}

UserTable::UserTable( InfUserTable *infUserTable,
    QObject *parent,
    bool own_gobject )
    : QGObject( G_OBJECT(infUserTable), parent, own_gobject )
{
}

}

