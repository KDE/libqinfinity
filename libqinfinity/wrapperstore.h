#ifndef QINFINITY_WRAPPER_STORE
#define QINFINITY_WRAPPER_STORE

#include <QObject>
#include <QMap>

#include <glib-object.h>

namespace QInfinity
{

class QGObject;

class WrapperStore
    : public QObject
{
    Q_OBJECT

    public:
        static WrapperStore *instance();

        QGObject *findWrapper( GObject *obj );
        void storeWrapper( GObject *obj, QGObject *wrapper );
        QGObject *takeWrapper( GObject *obj );

    protected:
        WrapperStore();

    private Q_SLOTS:
        void wrapperDestroyed( QObject *obj = 0 );

    private:
        QMap<GObject*, QGObject*> wrapperMap;
        QMap<QGObject*, GObject*> gobjMap;

};

}

#endif

