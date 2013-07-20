/*
 * Copyright 2013 Sven Brauch <svenbrauch@gmail.com>
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

#ifndef QINFINITY_UNDOGROUPING_H
#define QINFINITY_UNDOGROUPING_H

#include "qgobject.h"

#include <QPointer>

typedef struct _InfTextUndoGrouping InfTextUndoGrouping;

namespace QInfinity
{

class User;
class Session;

class UndoGrouping
    : public QGObject
{
    public:
        static QPointer<UndoGrouping> wrap( InfTextUndoGrouping *grouping,
            QObject *parent = 0,
            bool own_gobject = false );

        void initialize(const QInfinity::Session* session, const QInfinity::User* user);
        void beginGroup();
        void endGroup();
        bool hasOpenGroup() const;
        unsigned int undoSize() const;
        unsigned int redoSize() const;

    protected:
        UndoGrouping( InfTextUndoGrouping *grouping,
            QObject *parent = 0,
            bool own_gobject = false );

    private:
        bool m_hasOpenGroup;

};

}

#endif

