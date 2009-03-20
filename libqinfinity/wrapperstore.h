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
 * wrappers.  It also handles deletion of the wrapping
 * QGObject when the wrapped GObject is finalized.
 */
class WrapperStore
    : public QObject
{
    Q_OBJECT;

    public:
        /**
         * @brief Get an instance of the WrapperStore class.
         */
        static WrapperStore *instance();

        static void insertWrapper( GObject *object,
            QGObject *wrapper );

        static QGObject *getWrapper( GObject *object );

        /**
         * @brief Finds wrapper for obj
         * @return Found wrapper object, or NULL if none fond.
         */
        QGObject *findWrapper( GObject *obj );

        /**
         * @brief Store wrapper for gobject.
         *
         * If wrapper already exists for obj, the current wrapper
         * is deleted.  This can cause errors, so make sure to
         * check for an existing wrapper with findWrapper before
         * calling this.
         */
        void storeWrapper( GObject *obj,
            QGObject *wrapper );

    protected:
        WrapperStore();
        ~WrapperStore();

    private Q_SLOTS:
        void slotWrapperDeleted( QObject *wrapper );

    private:
        void removeWrapper( QGObject *wrapper );

        /*
         * We can use a single-valued hash here because there
         * should only be one stored wrapper per gobject instance.
         */
        QHash<GObject*, QGObject*> gobjToWrapper;

};

}

#endif

