#include <libinfinity/common/inf-init.h>

namespace QInfinity
{

void init()
{
    inf_init( 0 );
}

void deinit()
{
    inf_deinit();
}

}

