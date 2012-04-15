#include "ViewItemsWalkerCore.hpp"
#include "ViewItemsSessionWalkerNode.hpp"
#include "../ModuleViewItems.hpp"
#include "../ViewItem.hpp"
#include "../ViewItemsModulesMgr.hpp"

/**
 *
 */
CViewItemsWalkerCore::CViewItemsWalkerCore(CViewItemsModulesMgr& rViewItemsModulesMgr) :
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
CViewItemsWalkerCore::CViewItemsWalkerCore(const CViewItemsWalkerCore& walker) :
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
CViewItemsWalkerCore::~CViewItemsWalkerCore()
{
    m_rViewItemsModulesMgr.DetachWalker(this);

    ClearModuleNodes();
}


/**
 *
 */
void CViewItemsWalkerCore::OnNewModuleViewItem( CModuleViewItems* pModule )
{
    CViewItemsModuleWalkerNode*     pNode = new CViewItemsModuleWalkerNode(pModule);

    m_Nodes.push_back(pNode);
}


/**
 *
 */
void CViewItemsWalkerCore::OnNewSessionViewItem( CModuleViewItems* pModule, CSessionViewItems* pSession )
{
    CViewItemsModuleWalkerNode*         pModuleNode = GetNodeWithModule(pModule);
    CViewItemsSessionWalkerNode*        pSessionWalkerNode = new CViewItemsSessionWalkerNode(pSession);

    pModuleNode->AddNode(pSessionWalkerNode);
}


/**
 *
 */
void CViewItemsWalkerCore::OnNewViewItem( CViewItem* pViewItem )
{
    m_Height += pViewItem->GetSize().height();
}


/**
 *
 */
void CViewItemsWalkerCore::OnItemWidthChanged( CViewItem* pViewItem )
{
    m_Width = Nyx::Max( m_Width, (float)pViewItem->GetSize().width() );
}


/**
 *
 */
bool CViewItemsWalkerCore::InitNewModulesPosition()
{
    size_t          index = 0;
    bool            bModuleInitialized = false;

    while ( index < m_Nodes.size() )
        m_Nodes[index++]->InitModulePosition();

    return bModuleInitialized;
}


/**
 *
 */
bool CViewItemsWalkerCore::MoveToBegin()
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
bool CViewItemsWalkerCore::MoveToNext()
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
        CViewItemsModuleWalkerNode* pNode = m_Nodes[index];

        pNode->RefreshPositions();

        if ( !pNode->UpperPos().Valid() ) // attempt getting a valid upper position in case new data came in
        {
            if ( pNode->LowerPos().Valid() )
                pNode->MoveToNext();
            else
                pNode->MoveToBegin();
        }

        while ( pNode->UpperPos().Valid() && pNode->UpperPos().IsBefore(m_Pos) )
        {
            m_Pos.Y() += pNode->LowerPos().Item()->GetSize().height();
            ++ m_LineNumber;
            pNode->MoveToNext();
        }

        if ( pos.Valid() )
        {
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

        CViewItem*  pNewItem = pos.Item();

        if ( pNewItem->GetOwner() != Item()->GetOwner() )
            ++ m_LineNumber;

        m_Pos = pos;

        m_Nodes[pos.ModuleNodeId()]->MoveToNext();

        return true;
    }

    return false;
}


/**
 *
 */
bool CViewItemsWalkerCore::MoveToPrevious()
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
        CViewItemsModuleWalkerNode*   pNode = m_Nodes[index];
        pNode->RefreshPositions();

        if ( pos.Valid() )
        {

            if ( pNode->LowerPos().Valid() && pNode->LowerPos().IsAfter(pos))
            {
                pos = pNode->LowerPos();
                pos.ModuleNodeId() = index;
            }
        }
        else
        {
            pos = pNode->LowerPos();
            pos.ModuleNodeId() = index;
        }
    }

    if ( pos.Valid() )
    {
        pos.Y() = m_Pos.Y() - m_Pos.Item()->GetSize().height();

        CViewItem*  pNewItem = pos.Item();

        if ( pNewItem->GetOwner() != Item()->GetOwner() )
            -- m_LineNumber;

        m_Pos = pos;

        m_Nodes[pos.ModuleNodeId()]->MoveToPrevious();
//        -- m_LineNumber;
        return true;
    }

    return false;
}


/**
 *
 */
bool CViewItemsWalkerCore::MoveTo(const float& y)
{
    while ( m_Pos.Valid() && m_Pos.Y() + m_Pos.Item()->GetSize().height() < y && MoveToNext() );
    while ( m_Pos.Valid() && m_Pos.Y() > y && MoveToPrevious() );

    return ( m_Pos.Valid() && m_Pos.Y() <= y && m_Pos.Y() + m_Pos.Item()->GetSize().height() >= y );
}


/**
 *
 */
void CViewItemsWalkerCore::PushState()
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
void CViewItemsWalkerCore::PopState()
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
const CViewItemsWalkerCore& CViewItemsWalkerCore::operator = (const CViewItemsWalkerCore& walker)
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
CViewItemsModuleWalkerNode* CViewItemsWalkerCore::GetNodeWithModule( CModuleViewItems* pModule ) const
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
void CViewItemsWalkerCore::CopyDataFrom(const CViewItemsWalkerCore& walker)
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
void CViewItemsWalkerCore::ClearModuleNodes()
{
    for (size_t index = 0; index < m_Nodes.size(); ++index)
        delete m_Nodes[index];
}
