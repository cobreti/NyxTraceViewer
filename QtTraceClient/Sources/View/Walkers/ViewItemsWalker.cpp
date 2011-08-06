#include "ViewItemsWalker.hpp"
#include "ViewItemsSessionWalkerNode.hpp"
#include "../ModuleViewItems.hpp"
#include "../ViewItem.hpp"
#include "../ViewItemsModulesMgr.hpp"

/**
 *
 */
CViewItemsWalker::CViewItemsWalker(CViewItemsModulesMgr& rViewItemsModulesMgr) :
    m_Direction(eD_Undefined),
    m_LineNumber(0),
    m_Height(0.0f),
    m_Width(0.0f),
    m_rViewItemsModulesMgr(rViewItemsModulesMgr)
{
    m_rViewItemsModulesMgr.AttachWalker(this);
}


/**
 *
 */
CViewItemsWalker::CViewItemsWalker(const CViewItemsWalker& walker) :
    m_Height(walker.m_Height),
    m_Width(walker.m_Width),
    m_rViewItemsModulesMgr(walker.m_rViewItemsModulesMgr)
{
    m_rViewItemsModulesMgr.AttachWalker(this);

    CopyDataFrom(walker);
}


/**
 *
 */
CViewItemsWalker::~CViewItemsWalker()
{
    m_rViewItemsModulesMgr.DetachWalker(this);

    ClearModuleNodes();
}


/**
 *
 */
void CViewItemsWalker::OnNewModuleViewItem( CModuleViewItems* pModule )
{
    CViewItemsModuleWalkerNode*     pNode = new CViewItemsModuleWalkerNode(pModule);

    m_Nodes.push_back(pNode);
}


/**
 *
 */
void CViewItemsWalker::OnNewSessionViewItem( CModuleViewItems* pModule, CSessionViewItems* pSession )
{
    CViewItemsModuleWalkerNode*         pModuleNode = GetNodeWithModule(pModule);
    CViewItemsSessionWalkerNode*        pSessionWalkerNode = new CViewItemsSessionWalkerNode(pSession);

    pModuleNode->AddNode(pSessionWalkerNode);
}


/**
 *
 */
void CViewItemsWalker::OnNewViewItem( CViewItem* pViewItem )
{
    m_Height += pViewItem->GetSize().height();
}


/**
 *
 */
void CViewItemsWalker::OnItemWidthChanged( CViewItem* pViewItem )
{
    m_Width = Nyx::Max( m_Width, (float)pViewItem->GetSize().width() );
}


/**
 *
 */
bool CViewItemsWalker::InitNewModulesPosition()
{
    size_t          index = 0;
    bool            bModuleInitialized = false;

    while ( index < m_Nodes.size() )
    {
        CViewItemsModuleWalkerNode*   pNode = m_Nodes[index];

        if ( !pNode->ValidPos() )
            pNode->MoveToBegin();

        ++ index;
    }

    return bModuleInitialized;
}


/**
 *
 */
bool CViewItemsWalker::MoveToBegin()
{
    if ( m_Nodes.empty() )
        return false;

    m_Pos = CViewItemsWalkerPos();

    size_t          index = 0;

    while ( index < m_Nodes.size() )
    {
        if ( m_Nodes[index]->MoveToBegin() )
        {
            if ( !m_Pos.Valid() )
            {
                m_Pos = m_Nodes[index]->UpperPos();
                m_Pos.ModuleNodeId() = index;
            }

            if ( m_Nodes[index]->UpperPos().IsBefore(m_Pos) )
            {
                m_Pos = m_Nodes[index]->UpperPos();
                m_Pos.ModuleNodeId() = index;
            }
        }

        ++ index;
    }

    m_Direction = eD_Undefined;
    m_LineNumber = 1;

    if ( m_Pos.Valid() )
    {
        m_Nodes[m_Pos.ModuleNodeId()]->MoveToNext();
        return true;
    }

    return false;
}


/**
 *
 */
bool CViewItemsWalker::MoveToNext()
{
    if ( m_Nodes.empty() || !m_Pos.Valid() )
        return false;

    CViewItemsModuleWalkerNode*     pCurrentModuleWalker = m_Nodes[m_Pos.ModuleNodeId()];

    if ( m_Direction == eD_Decreasing )
        pCurrentModuleWalker->MoveToNext();

    m_Direction = eD_Increasing;

    size_t                      index = 0;
    CViewItemsWalkerPos         pos;

    float CurrentLineHeight = m_Pos.Item()->GetSize().height();

    for ( index = 0; index < m_Nodes.size(); ++index)
    {
        if ( pos.Valid() )
        {
            const CViewItemsModuleWalkerNode*   pNode = m_Nodes[index];

            if ( pNode->UpperPos().Valid() && pNode->UpperPos().IsBefore(pos) )
            {
                pos = pNode->UpperPos();
                pos.ModuleNodeId() = index;
            }
        }
        else
        {
            pos = m_Nodes[index]->UpperPos();
            pos.ModuleNodeId() = index;
        }
    }

    if ( pos.Valid() )
    {
        pos.Y() = m_Pos.Y() + CurrentLineHeight;
        m_Pos = pos;

        m_Nodes[pos.ModuleNodeId()]->MoveToNext();

        ++ m_LineNumber;
        return true;
    }

    return false;
}


/**
 *
 */
bool CViewItemsWalker::MoveToPrevious()
{
    if ( m_Nodes.empty() || !m_Pos.Valid() )
        return false;

    CViewItemsModuleWalkerNode*     pCurrentModuleWalker = m_Nodes[m_Pos.ModuleNodeId()];

    if ( m_Direction == eD_Increasing )
        pCurrentModuleWalker->MoveToPrevious();

    m_Direction = eD_Decreasing;

    size_t                  index = 0;
    CViewItemsWalkerPos     pos;

    for (index = 0; index < m_Nodes.size(); ++index)
    {
        if ( pos.Valid() )
        {
            const CViewItemsModuleWalkerNode*   pNode = m_Nodes[index];

            if ( pNode->LowerPos().Valid() && pNode->LowerPos().IsAfter(pos))
            {
                pos = pNode->LowerPos();
                pos.ModuleNodeId() = index;
            }
        }
        else
        {
            pos = m_Nodes[index]->LowerPos();
            pos.ModuleNodeId() = index;
        }
    }

    if ( pos.Valid() )
    {
        pos.Y() = m_Pos.Y() - m_Pos.Item()->GetSize().height();
        m_Pos = pos;

        m_Nodes[pos.ModuleNodeId()]->MoveToPrevious();
        -- m_LineNumber;
        return true;
    }

    return false;
}


/**
 *
 */
bool CViewItemsWalker::MoveTo(const float& y)
{
    if ( m_Pos.Valid() && m_Pos.Y() + m_Pos.Item()->GetSize().height() < y )
    {
        while ( m_Pos.Valid() && m_Pos.Y() + m_Pos.Item()->GetSize().height() < y && MoveToNext() );
    }
    else if ( m_Pos.Valid() && m_Pos.Y() > y )
    {
        while ( m_Pos.Valid() && m_Pos.Y() > y && MoveToPrevious() );
    }

    return ( m_Pos.Valid() && m_Pos.Y() <= y && m_Pos.Y() + m_Pos.Item()->GetSize().height() >= y );
}


/**
 *
 */
void CViewItemsWalker::PushState()
{
    for (size_t index = 0; index < m_Nodes.size(); ++index)
        m_Nodes[index]->PushState();

    m_PositionStack.push_back(m_Pos);
    m_DirectionStack.push_back(m_Direction);
    m_LineNumberStack.push_back(m_LineNumber);
}


/**
 *
 */
void CViewItemsWalker::PopState()
{
    for (size_t index = 0; index < m_Nodes.size(); ++index)
        m_Nodes[index]->PopState();

    if ( !m_PositionStack.empty())
    {
        m_Pos = m_PositionStack.back();
        m_PositionStack.pop_back();
    }

    if ( !m_DirectionStack.empty())
    {
        m_Direction = m_DirectionStack.back();
        m_DirectionStack.pop_back();
    }

    if ( !m_LineNumberStack.empty())
    {
        m_LineNumber = m_LineNumberStack.back();
        m_LineNumberStack.pop_back();
    }
}


/**
 *
 */
const CViewItemsWalker& CViewItemsWalker::operator = (const CViewItemsWalker& walker)
{
    if ( this == &walker )
        return *this;

    ClearModuleNodes();
    CopyDataFrom(walker);

    return *this;
}


/**
 *
 */
CViewItemsModuleWalkerNode* CViewItemsWalker::GetNodeWithModule( CModuleViewItems* pModule ) const
{
    size_t          index = 0;

    while ( index < m_Nodes.size())
    {
        if ( m_Nodes[index]->ContainsModule(pModule) )
            return m_Nodes[index];

        ++ index;
    }

    return NULL;
}


/**
 *
 */
void CViewItemsWalker::CopyDataFrom(const CViewItemsWalker& walker)
{
    m_Height = walker.m_Height;
    m_Width = walker.m_Width;
    m_Direction = walker.m_Direction;
    m_Nodes.resize(walker.m_Nodes.size());
    m_Pos = walker.m_Pos;
    m_LineNumber = walker.m_LineNumber;

    for (size_t index = 0; index < walker.m_Nodes.size(); ++index)
    {
        m_Nodes[index] = new CViewItemsModuleWalkerNode(*walker.m_Nodes[index]);
    }
}


/**
 *
 */
void CViewItemsWalker::ClearModuleNodes()
{
    for (size_t index = 0; index < m_Nodes.size(); ++index)
        delete m_Nodes[index];
}
