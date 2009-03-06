#ifndef QINFINITY_BROWSER_ITER_H
#define QINFINITY_BROWSER_ITER_H

#include <libinfinity/client/infc-browser.h>

#include <QString>

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
{

    public:
        /**
         * @brief Create an iterator pointing to root node of browser
         */
        BrowserIter( const Browser &browser );
        BrowserIter( const InfcBrowserIter *infIter,
            InfcBrowser *infBrowser );
        BrowserIter( const BrowserIter &other );

        BrowserIter &operator++();
        BrowserIter operator++( int );
        BrowserIter &operator--();
        BrowserIter operator--( int );
        BrowserIter &operator=( const BrowserIter &other );
        
        bool next();
        bool prev();
        bool child();
        bool parent();
        bool isDirectory();
        InfcExploreRequest *explore();
        bool isExplored();
        QString name();
        QString path();
        Browser *browser() const;
        InfcBrowser *infBrowser() const;
        const InfcBrowserIter *infBrowserIter() const;
        InfcBrowserIter *infBrowserIter();
        QString noteType();

    private:
        InfcBrowser *m_infBrowser;
        InfcBrowserIter m_infBrowserIter;

};

}

#endif

