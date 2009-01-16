/*
 *  Copyright (c) 2008 Cyrille Berger <cberger@cberger.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "./kis_node_commands_adapter.h"

#include "kis_undo_adapter.h"
#include "kis_image.h"
#include "commands/kis_image_layer_add_command.h"
#include "commands/kis_image_layer_move_command.h"
#include "commands/kis_image_layer_remove_command.h"
#include "kis_view2.h"

KisNodeCommandsAdapter::KisNodeCommandsAdapter( KisView2 * view ) : m_view( view )
{
    
}

KisNodeCommandsAdapter::~KisNodeCommandsAdapter()
{
    
}

void KisNodeCommandsAdapter::addNode(KisNodeSP node, KisNodeSP parent, KisNodeSP aboveThis )
{
    Q_ASSERT(m_view->image()->undoAdapter());
    m_view->image()->undoAdapter()->addCommand( new KisImageLayerAddCommand( m_view->image(), node, parent, aboveThis ) );
}

void KisNodeCommandsAdapter::addNode(KisNodeSP node, KisNodeSP parent, quint32 index )
{
    Q_ASSERT(m_view->image()->undoAdapter());
    m_view->image()->undoAdapter()->addCommand( new KisImageLayerAddCommand( m_view->image(), node, parent, index ) );
}

void KisNodeCommandsAdapter::moveNode(KisNodeSP node, KisNodeSP parent, KisNodeSP aboveThis )
{
    Q_ASSERT(m_view->image()->undoAdapter());
    m_view->image()->undoAdapter()->addCommand( new KisImageLayerMoveCommand( m_view->image(), node, parent, aboveThis ) );
}

void KisNodeCommandsAdapter::moveNode(KisNodeSP node, KisNodeSP parent, quint32 indexaboveThis )
{
    Q_ASSERT(m_view->image()->undoAdapter());
    m_view->image()->undoAdapter()->addCommand( new KisImageLayerMoveCommand( m_view->image(), node, parent, indexaboveThis ) );
}

void KisNodeCommandsAdapter::removeNode(KisNodeSP node)
{
    Q_ASSERT(m_view->image()->undoAdapter());
    m_view->image()->undoAdapter()->addCommand( new KisImageLayerRemoveCommand( m_view->image(), node ) );
}