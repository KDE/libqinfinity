/*
 * Copyright 2009  Gregory Haynes <greg@greghaynes.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QINFINITY_BROWSER_ITER_H
#define QINFINITY_BROWSER_ITER_H

#include <libinfinity/client/infc-browser.h>

#include <QString>
#include <QPointer>

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
        QString name() const;
        QString path() const;
        unsigned int id() const;
        QPointer<Browser> browser() const;
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

