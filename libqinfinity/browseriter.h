#ifndef QINFINITY_BROWSER_ITER_H
#define QINFINITY_BROWSER_ITER_H

#include <QObject>

#include <libinfinity/client/infc-browser.h>

namespace QInfinity
{

class Browser;

/**
 * @brief Provides ability to navigate a Browser.
 *
 * In most cases, BrowserIter's are initialized on
 * the stack.
 */
class BrowserIter
    : public QObject
{

    public:
        /**
         * @brief Create an iterator pointing to root node of browser
         */
        BrowserIter( const Browser &browser,
            QObject *parent = 0 );
        BrowserIter( const InfcBrowserIter *infIter,
            InfcBrowser *infBrowser,
            QObject *parent = 0 );
        BrowserIter( const BrowserIter &other,
            QObject *parent = 0 );

        BrowserIter &operator++();
        BrowserIter operator++( int );
        BrowserIter &operator--();
        BrowserIter operator--( int );
        
        bool next();
        bool prev();
        bool child();
        bool parent();
        InfcExploreRequest *explore();
        bool isExplored();
        const char *name();
        const char *path();
        InfcBrowser *infBrowser() const;
        const InfcBrowserIter *infBrowserIter() const;

    private:
        InfcBrowser *m_infBrowser;
        InfcBrowserIter m_infBrowserIter;

};

}

#endif

