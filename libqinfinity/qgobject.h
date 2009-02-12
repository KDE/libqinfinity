#ifndef QINFINITY_QGOBJECT_H
#define QINFINITY_QGOBJECT_H

#include <QMap>

#include <glib-object.h>

namespace QInfinity
{

/**
 * @brief Base class for classes wrapping a gobject
 */
class QGObject
{

    public:
        QGObject();
        QGObject( GObject *obj,
            bool own_gobj = true );
        ~QGObject();

        GObject *gobject() const;
        void setGobject( GObject *obj,
            bool own_gobj = true );

    private:
        GObject *m_gobject;
        bool m_own_gobj;

};

}

#endif

