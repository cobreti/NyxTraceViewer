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

        if ( !pNode->CachedPos().Valid() )
        {
            pNode->MoveToBegin();
        }

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
                m_Nodes[index]->GetPosData(m_Pos);

            if ( m_Nodes[index]->CachedPos().IsBefore(m_Pos) )
                m_Nodes[index]->GetPosData(m_Pos);
        }

        ++ index;
    }

    m_Pos.ConcurrentItemsVisited().clear();
    m_Pos.ConcurrentItemsVisited().insert( m_Pos.ItemId() );
    m_Direction = eD_Undefined;
    m_LineNumber = 1;

    return m_Pos.Valid();
}


/**
 *
 */
bool CViewItemsWalker::MoveToNext()
{
    if ( m_Nodes.empty() || !m_Pos.Valid() )
        return false;

    if ( m_Direction == eD_Decreasing )
        m_Pos.ConcurrentItemsVisited().clear();

    m_Direction = eD_Increasing;

    size_t              index = 0;
    bool                ChangedLine = false;
    ViewItemIDSet       InSet = m_Pos.ConcurrentItemsVisited();
    Nyx::CWString       FloorTickCount = m_Pos.ItemPos().Item()->TickCount();

    for ( index = 0; index < m_Nodes.size(); ++index)
        if ( !m_Nodes[index]->CachedPos().Valid() )
            m_Nodes[index]->MoveToBegin();

    m_Pos.Module()->MoveToNext();

    for ( index = 0; index < m_Nodes.size(); ++index )
    {
        CViewItemsModuleWalkerNode*   pNode = m_Nodes[index];

        while (     pNode->CachedPos().Valid() &&
                    pNode->CachedPos().IsBefore(m_Pos) &&
                    pNode->MoveToNext());
    }

    index = 0;

    float CurrentLineHeight = m_Pos.ItemPos().Item()->GetSize().height();

    //
    // Attemps to find a concurrent item first
    //
    for ( index = 0; index < m_Nodes.size() && !ChangedLine; ++index)
    {
        const CViewItemsModuleWalkerNode*   pNode = m_Nodes[index];

        if ( pNode->CachedPos().Valid() && m_Pos.IsConcurrent(pNode->CachedPos()) && InSet.count(pNode->CachedPos().ItemId()) == 0)
        {
            pNode->GetPosData(m_Pos);
            m_Pos.ConcurrentItemsVisited().insert( pNode->CachedPos().ItemId());
            ChangedLine = true;
        }
    }

    //
    // find the first line after the current one
    //
    for ( index = 0; index < m_Nodes.size() && !ChangedLine; ++index)
    {
        const CViewItemsModuleWalkerNode*   pNode = m_Nodes[index];

        if ( pNode->CachedPos().Valid() && m_Pos.IsBefore( pNode->CachedPos()) && pNode->CachedPos().ItemPos().Item()->TickCount() > FloorTickCount )
        {
            pNode->GetPosData(m_Pos);
            m_Pos.ConcurrentItemsVisited().clear();
            m_Pos.ConcurrentItemsVisited().insert( pNode->CachedPos().ItemId());
            ChangedLine = true;
            break;
        }
    }

    if ( ChangedLine )
    {
        //
        // check if any line could be before the found one
        //
        while ( index < m_Nodes.size())
        {
            const CViewItemsModuleWalkerNode*   pNode = m_Nodes[index];

            if ( pNode->CachedPos().Valid() && pNode->CachedPos().IsBefore(m_Pos) && pNode->CachedPos().ItemPos().Item()->TickCount() > FloorTickCount && InSet.count(pNode->CachedPos().ItemId()) == 0)
            {
                pNode->GetPosData(m_Pos);
                m_Pos.ConcurrentItemsVisited().clear();
                m_Pos.ConcurrentItemsVisited().insert( pNode->CachedPos().ItemId());
            }

            ++ index;
        }

        m_Pos.Y() += CurrentLineHeight;
        ++ m_LineNumber;
    }

    return ChangedLine && m_Pos.Valid();
}


/**
 *
 */
bool CViewItemsWalker::MoveToPrevious()
{
    if ( m_Nodes.empty() || !m_Pos.Valid() )
        return false;

    if ( m_Direction == eD_Increasing )
        m_Pos.ConcurrentItemsVisited().clear();

    m_Direction = eD_Decreasing;

    size_t              index = 0;
    bool                FoundNewLine = false;
    ViewItemIDSet       InSet = m_Pos.ConcurrentItemsVisited();
    Nyx::CWString       CeilingTickCount = m_Pos.ItemPos().Item()->TickCount();

    for ( index = 0; index < m_Nodes.size(); ++index)
        if ( !m_Nodes[index]->CachedPos().Valid() )
            m_Nodes[index]->MoveToBegin();

    m_Pos.Module()->MoveToPrevious();

    for ( index = 0; index < m_Nodes.size(); ++index )
    {
        CViewItemsModuleWalkerNode*   pNode = m_Nodes[index];

        while (     pNode->CachedPos().Valid() &&
                    m_Pos.IsBefore(pNode->CachedPos()) &&
                    pNode->MoveToPrevious());
    }

    //
    // Attemps to find a concurrent item first
    //
    for ( index = 0; index < m_Nodes.size() && !FoundNewLine; ++index)
    {
        const CViewItemsModuleWalkerNode*   pNode = m_Nodes[index];

        if ( pNode->CachedPos().Valid() && m_Pos.IsConcurrent(pNode->CachedPos()) && InSet.count(pNode->CachedPos().ItemId()) == 0)
        {
            pNode->GetPosData(m_Pos);
            m_Pos.ConcurrentItemsVisited().insert( pNode->CachedPos().ItemId());
            FoundNewLine = true;
        }
    }


    //
    // check for any line before this one
    //
    for (index = 0; index < m_Nodes.size() && !FoundNewLine; ++index)
    {
        const CViewItemsModuleWalkerNode*   pNode = m_Nodes[index];

        if (pNode->CachedPos().Valid() && m_Pos.IsAfter(pNode->CachedPos()) && pNode->CachedPos().ItemPos().Item()->TickCount() < CeilingTickCount )
        {
            pNode->GetPosData(m_Pos);
            m_Pos.ConcurrentItemsVisited().clear();
            m_Pos.ConcurrentItemsVisited().insert( pNode->CachedPos().ItemId());
            FoundNewLine = true;
            break;
        }

        ++ index;
    }

    if ( FoundNewLine )
    {
        //
        // check if any line could be before the found one
        //
        while ( index < m_Nodes.size())
        {
            const CViewItemsModuleWalkerNode*   pNode = m_Nodes[index];

            if ( pNode->CachedPos().Valid() && pNode->CachedPos().IsAfter(m_Pos) && pNode->CachedPos().ItemPos().Item()->TickCount() < CeilingTickCount && InSet.count(pNode->CachedPos().ItemId()) == 0 )
            {
                pNode->GetPosData(m_Pos);
                m_Pos.ConcurrentItemsVisited().clear();
                m_Pos.ConcurrentItemsVisited().insert( pNode->CachedPos().ItemId());
            }

            ++ index;
        }

        m_Pos.Y() -= m_Pos.ItemPos().Item()->GetSize().height();
        -- m_LineNumber;
    }

    return FoundNewLine && m_Pos.Valid();
}


/**
 *
 */
bool CViewItemsWalker::MoveTo(const float& y)
{
    if ( m_Pos.Valid() && m_Pos.Y() + m_Pos.ItemPos().Item()->GetSize().height() < y )
    {
        while ( m_Pos.Valid() && m_Pos.Y() + m_Pos.ItemPos().Item()->GetSize().height() < y && MoveToNext() );
    }
    else if ( m_Pos.Valid() && m_Pos.Y() > y )
    {
        while ( m_Pos.Valid() && m_Pos.Y() > y && MoveToPrevious() );
    }

    return ( m_Pos.Valid() && m_Pos.Y() <= y && m_Pos.Y() + m_Pos.ItemPos().Item()->GetSize().height() >= y );
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

        if ( m_Pos.Module() == walker.m_Nodes[index])
            m_Pos.Module() = m_Nodes[index];
    }

    if ( m_Pos.Module() )
        m_Pos.Session() = m_Pos.Module()->GetEquivalentSession(walker.m_Pos.Module(), walker.m_Pos.Session());
}


/**
 *
 */
void CViewItemsWalker::ClearModuleNodes()
{
    for (size_t index = 0; index < m_Nodes.size(); ++index)
        delete m_Nodes[index];
}
