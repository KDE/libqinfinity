#ifndef QINFINITY_WRAPPER_STORE
#define QINFINITY_WRAPPER_STORE

#include <QObject>
#include <QMap>
#include <QPointer>

#include <glib-object.h>

namespace QInfinity
{

class QGObject;

class WrapperIndex
{

    public:
        WrapperIndex( QGObject *wrapper,
            bool own_object );
        ~WrapperIndex();

        QGObject *wrapper() const;
        bool isOwner() const;
        void setOwner( bool own_object );

    private:
        QPointer<QGObject> m_wrapper;
        bool m_own_object;

};

class WrapperStore
    : public QObject
{
    Q_OBJECT

    public:
        static WrapperStore *instance();

        /**
         * @brief Finds wrapper for obj
         * @return Found wrapper object, or NULL if none fond.
         */
        QGObject *findWrapper( GObject *obj );
        void storeWrapper( GObject *obj,
            QGObject *wrapper,
            bool own_wrapper );
        QGObject *takeWrapper( GObject *obj );

    protected:
        WrapperStore();
        ~WrapperStore();

    private Q_SLOTS:
        void wrapperDestroyed( QObject *obj = 0 );

    private:
        WrapperIndex *findWrapperIndex( GObject *obj );
        GObject *findGobject( QGObject *obj );

        QMap<GObject*, WrapperIndex*> gobjToWrapperMap;
        QMap<QGObject*, GObject*> qToGobjMap;

};

}

#endif

