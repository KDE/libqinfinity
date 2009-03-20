#include "usertable.h"
#include "wrapperstore.h"

namespace QInfinity
{

UserTable *UserTable::create( InfUserTable *infUserTable,
    QObject *parent )
{
    WrapperStore *store = WrapperStore::instance();
    UserTable *table = dynamic_cast<UserTable*>(store->findWrapper( G_OBJECT(infUserTable) ));
    if( !table )
        table = new UserTable( infUserTable, parent );
    return table;
}

UserTable::UserTable( InfUserTable *infUserTable,
    QObject *parent )
    : QGObject( G_OBJECT(infUserTable), parent )
{
}

}

