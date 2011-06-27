#include "ViewItemsWalker.hpp"
#include "ViewItemsSessionWalkerNode.hpp"
#include "../ModuleViewItems.hpp"
#include "../ViewItem.hpp"

/**
 *
 */
CViewItemsWalker::CViewItemsWalker()
{
}


/**
 *
 */
CViewItemsWalker::~CViewItemsWalker()
{
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
bool CViewItemsWalker::MoveToBegin()
{
    if ( m_Nodes.empty() )
        return false;

    m_Pos = CViewItemsWalkerPos();

    TViewItemsModuleWalkerNodeList::const_iterator  NodeIter = m_Nodes.begin();

    while ( NodeIter != m_Nodes.end() )
    {
        if ( (*NodeIter)->MoveToBegin() )
        {
            if ( !m_Pos.Valid() )
                (*NodeIter)->GetPosData(m_Pos);

            if ( m_Pos < (*NodeIter)->CachedPos() )
                (*NodeIter)->GetPosData(m_Pos);
        }

        ++ NodeIter;
    }

    return m_Pos.Valid();
}


/**
 *
 */
bool CViewItemsWalker::MoveToNext()
{
    if ( m_Nodes.empty() || !m_Pos.Valid() )
        return false;

    TViewItemsModuleWalkerNodeList::const_iterator  NodeIter = m_Nodes.begin();
    bool                                            ChangedLine = false;

    m_Pos.Module()->MoveToNext();

    float CurrentLineHeight = m_Pos.ItemPos().Item()->GetSize().height();

    while ( NodeIter != m_Nodes.end() )
    {
        if ( (*NodeIter)->CachedPos().Valid() && m_Pos < (*NodeIter)->CachedPos() )
        {
            (*NodeIter)->GetPosData(m_Pos);
            ChangedLine = true;
        }

        ++ NodeIter;
    }

    if ( ChangedLine )
    {
        m_Pos.Y() += CurrentLineHeight;
    }

    return m_Pos.Valid();
}


/**
 *
 */
bool CViewItemsWalker::MoveToPrevious()
{
    if ( m_Nodes.empty() || !m_Pos.Valid() )
        return false;

    TViewItemsModuleWalkerNodeList::const_iterator  NodeIter = m_Nodes.begin();
    bool                                            FoundNewLine = false;

    m_Pos.Module()->MoveToPrevious();

    while ( NodeIter != m_Nodes.end() )
    {
        if ( (*NodeIter)->CachedPos().Valid() && (*NodeIter)->CachedPos() < m_Pos )
        {
            (*NodeIter)->GetPosData(m_Pos);
            FoundNewLine = true;
        }

        ++ NodeIter;
    }

    if ( FoundNewLine )
    {
        m_Pos.Y() -= m_Pos.ItemPos().Item()->GetSize().height();
    }

    return m_Pos.Valid();
}


/**
 *
 */
bool CViewItemsWalker::MoveTo(const float& y)
{
    while ( m_Pos.Valid() && m_Pos.Y() + m_Pos.ItemPos().Item()->GetSize().height() < y && MoveToNext() );

    while ( m_Pos.Valid() && m_Pos.Y() > y && MoveToPrevious() );

    return ( m_Pos.Valid() && m_Pos.Y() <= y && m_Pos.Y() + m_Pos.ItemPos().Item()->GetSize().height() >= y );
}


/**
 *
 */
CViewItemsModuleWalkerNode* CViewItemsWalker::GetNodeWithModule( CModuleViewItems* pModule ) const
{
    TViewItemsModuleWalkerNodeList::const_iterator        pos = m_Nodes.begin();

    while ( pos != m_Nodes.end())
    {
        if ( (*pos)->ContainsModule(pModule) )
            return *pos;

        ++pos;
    }

    return NULL;
}
