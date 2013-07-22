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

        /**
         * @brief Sets the algorithm and user from the given session and user.
         * You must call this before calling beginGroup() or endGroup().
         * @param session The Session instance for the document in question
         * @param user The user for the document
         */
        void initialize(const QInfinity::Session* session, const QInfinity::User* user);

        /**
         * @brief Begins a new undo group.
         * All requests doine until the next call to endGroup() will be undone in one chunk.
         */
        void beginGroup();

        /**
         * @brief Ends an undo group.
         * The calls have to match a beginGroup() call done before.
         * @see beginGroup()
         */
        void endGroup();

        /**
         * @brief Returns true of there's an active undo group (started with beginGroup()).
         * @return bool true if there is a group, false otherwise.
         */
        bool hasOpenGroup() const;

        /**
         * @brief Return the amount of operations which should be undone if the user request an undo operation now.
         * Pass this value to Session::undo as its second parameter, if you want to
         * perform a grouped undo.
         * @see redoSize
         * @return unsigned int amount of operations to be undone
         */
        unsigned int undoSize() const;

        /**
         * @brief Returns the amount of operations which should be redone if the user request a redo operation now.
         * Pass this value to Session::redo as its second parameter, if you want to
         * perform a grouped redo.
         * @see undoSize
         * @return unsigned int amount of operations to be redone
         */
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

