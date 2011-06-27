#include "ViewItemsModuleWalkerNode.hpp"
#include "ViewItemsSessionWalkernode.hpp"
#include "../ModuleViewItems.hpp"


/**
 *
 */
CViewItemsModuleWalkerNode::CViewItemsModuleWalkerNode(CModuleViewItems* pModuleViewItems) :
    CViewItemsWalkerNode(),
    m_pModuleViewItems(pModuleViewItems)
{
    m_CachedPos.Module() = this;
}


/**
 *
 */
CViewItemsModuleWalkerNode::~CViewItemsModuleWalkerNode()
{
}


/**
 *
 */
bool CViewItemsModuleWalkerNode::ContainsModule( CModuleViewItems* pModule ) const
{
    return (m_pModuleViewItems->Name() == pModule->Name());
}


/**
 *
 */
void CViewItemsModuleWalkerNode::AddNode( CViewItemsSessionWalkerNode* pNode )
{
    m_ChildNodes.push_back(pNode);
}


/**
 *
 */
bool CViewItemsModuleWalkerNode::MoveToBegin()
{
    if ( m_ChildNodes.empty() )
        return false;

    CViewItemsSessionWalkerNode*        pNode = m_ChildNodes.front();

    return pNode->GetTopPos(m_CachedPos);
}


/**
 *
 */
bool CViewItemsModuleWalkerNode::MoveToNext()
{
    if ( !m_CachedPos.Valid() )
        return false;

    ++ m_CachedPos.ItemPos();

    if ( !m_CachedPos.Valid() )
    {
        CViewItemsSessionWalkerNode*        pNextSession = GetNextSession(m_CachedPos.Session());
        return pNextSession->GetTopPos(m_CachedPos);
    }

    return true;
}


/**
 *
 */
bool CViewItemsModuleWalkerNode::MoveToPrevious()
{
    if ( !m_CachedPos.Valid() )
        return false;

    -- m_CachedPos.ItemPos();

    if ( !m_CachedPos.Valid() )
    {
        CViewItemsSessionWalkerNode*        pPreviousSession = GetPreviousSession(m_CachedPos.Session());
        return pPreviousSession->GetLastPos(m_CachedPos);
    }

    return true;
}


/**
 *
 */
void CViewItemsModuleWalkerNode::GetPosData( CViewItemsWalkerPos& walkerPos ) const
{
    walkerPos.ItemPos() = m_CachedPos.ItemPos();
    walkerPos.Module() = m_CachedPos.Module();
    walkerPos.Session() = m_CachedPos.Session();
}


/**
 *
 */
CViewItemsSessionWalkerNode* CViewItemsModuleWalkerNode::GetNextSession( CViewItemsSessionWalkerNode* pSession ) const
{
    CViewItemsSessionWalkerNode*                            pNextSession = NULL;
    TViewItemsSessionWalkerNodeList::const_iterator         NodeIter = m_ChildNodes.begin();

    while ( NodeIter != m_ChildNodes.end() )
    {
        if ( *NodeIter == pSession )
        {
            ++ NodeIter;
            if ( NodeIter != m_ChildNodes.end() )
                pNextSession = *NodeIter;
            break;
        }

        ++ NodeIter;
    }

    return pNextSession;
}


/**
 *
 */
CViewItemsSessionWalkerNode* CViewItemsModuleWalkerNode::GetPreviousSession( CViewItemsSessionWalkerNode* pSession ) const
{
    CViewItemsSessionWalkerNode*                            pPreviousSession = NULL;
    TViewItemsSessionWalkerNodeList::const_iterator         NodeIter = m_ChildNodes.end();

    -- NodeIter;
    while ( NodeIter != m_ChildNodes.begin() )
    {
        if ( *NodeIter == pSession )
        {
            -- NodeIter;
            pPreviousSession = *NodeIter;
            break;
        }

        -- NodeIter;
    }

    return pPreviousSession;
}


