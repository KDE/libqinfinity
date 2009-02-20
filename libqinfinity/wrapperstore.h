#ifndef QINFINITY_WRAPPER_STORE
#define QINFINITY_WRAPPER_STORE

#include <QObject>
#include <QMultiHash>
#include <QPointer>

#include <glib-object.h>

namespace QInfinity
{

class QGObject;

/**
 * @brief Maps gobject instances to its QGObject wrapper.
 *
 * The WrapperStore maps GObject instances to their QGObject
 * wrappers.
 */
class WrapperStore
    : public QObject
{
    Q_OBJECT

    public:
        /**
         * @brief Get an instance of the WrapperStore class.
         */
        static WrapperStore *instance();

        /**
         * @brief Finds wrapper for obj
         * @return Found wrapper object, or NULL if none fond.
         */
        QGObject *findWrapper( GObject *obj );

        /**
         * @brief Store wrapper for gobject.
         */
        void storeWrapper( GObject *obj,
            QGObject *wrapper,
            bool own_wrapper );

    protected:
        WrapperStore();
        ~WrapperStore();

    private:

        /*
         * We can use a single-valued hash here because there
         * should only be one stored wrapper per gobject instance.
         */
        QHash<GObject*, QPointer<QGObject> > gobjToWrapper;

};

}

#endif

