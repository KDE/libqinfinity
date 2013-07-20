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

#include "undogrouping.h"
#include "wrapperstore.h"
#include "user.h"
#include "session.h"

#include <libinftext/inf-text-undo-grouping.h>
#include <libinftext/inf-text-user.h>
#include <libinfinity/adopted/inf-adopted-algorithm.h>
#include <libinfinity/adopted/inf-adopted-session.h>

namespace QInfinity
{

QPointer<UndoGrouping> UndoGrouping::wrap( InfTextUndoGrouping *infgrouping,
    QObject *parent,
    bool own_gobject )
{
    Q_ASSERT( INF_TEXT_IS_UNDO_GROUPING(infgrouping) );
    QGObject *wrapptr = WrapperStore::getWrapper( G_OBJECT(infgrouping), own_gobject );
    if ( wrapptr ) {
        return dynamic_cast<UndoGrouping*>(wrapptr);
    }
    UndoGrouping *grouping = new UndoGrouping( infgrouping, parent, own_gobject );
    return grouping;
}

UndoGrouping::UndoGrouping( InfTextUndoGrouping *grouping,
    QObject *parent,
    bool own_gobject )
    : QGObject( G_OBJECT(grouping), parent, own_gobject )
    , m_hasOpenGroup(false)
{
}

void UndoGrouping::initialize(const Session* session, const User* user)
{
    inf_adopted_undo_grouping_set_algorithm(
        INF_ADOPTED_UNDO_GROUPING(gobject()),
        inf_adopted_session_get_algorithm(INF_ADOPTED_SESSION(session->gobject())),
        INF_ADOPTED_USER(user->gobject())
    );
}

unsigned int UndoGrouping::undoSize() const
{
    return inf_adopted_undo_grouping_get_undo_size( INF_ADOPTED_UNDO_GROUPING(gobject()) );
}

unsigned int UndoGrouping::redoSize() const
{
    return inf_adopted_undo_grouping_get_redo_size( INF_ADOPTED_UNDO_GROUPING(gobject()) );
}

bool UndoGrouping::hasOpenGroup() const
{
    return m_hasOpenGroup;
}

void UndoGrouping::beginGroup()
{
    Q_ASSERT( ! m_hasOpenGroup );
    inf_adopted_undo_grouping_start_group( INF_ADOPTED_UNDO_GROUPING(gobject()), false );
    m_hasOpenGroup = true;
}

void UndoGrouping::endGroup()
{
    Q_ASSERT( m_hasOpenGroup );
    inf_adopted_undo_grouping_end_group( INF_ADOPTED_UNDO_GROUPING(gobject()), false );
    m_hasOpenGroup = false;
}

}

