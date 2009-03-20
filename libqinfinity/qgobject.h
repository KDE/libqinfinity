#ifndef QINFINITY_QGOBJECT_H
#define QINFINITY_QGOBJECT_H

#include <glib-object.h>

#include <QObject>

namespace QInfinity
{

/**
 * @brief Base class for classes wrapping a gobject
 */
class QGObject
    : public QObject
{

    public:
        QGObject( QObject *parent = 0 );
        ~QGObject();

        GObject *gobject() const;
        void setGobject( GObject *obj,
            bool own_gobj = true );

    protected:
        QGObject( GObject *obj,
            bool own_gobj = true,
            QObject *parent = 0 );

    private:
        GObject *m_gobject;
        bool m_own_gobj;

};

}

#endif

