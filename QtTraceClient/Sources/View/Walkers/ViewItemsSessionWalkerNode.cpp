#include "ViewItemsSessionWalkerNode.hpp"
#include "ViewItemsWalkerNodePos.hpp"
#include "../SessionViewItems.hpp"


/**
 *
 */
CViewItemsSessionWalkerNode::CViewItemsSessionWalkerNode(CSessionViewItems* pSession) :
    CViewItemsWalkerNode(),
    m_pSession(pSession)
{
}


/**
 *
 */
CViewItemsSessionWalkerNode::CViewItemsSessionWalkerNode(const CViewItemsSessionWalkerNode& node) :
    CViewItemsWalkerNode(),
    m_pSession(node.m_pSession)
{
}


/**
 *
 */
CViewItemsSessionWalkerNode::~CViewItemsSessionWalkerNode()
{
}


/**
 *
 */
bool CViewItemsSessionWalkerNode::GetTopPos( CViewItemsWalkerNodePos& walkerPos )
{
    walkerPos = m_pSession->Items().begin();
    return walkerPos.Valid();
}


/**
 *
 */
bool CViewItemsSessionWalkerNode::GetLastPos( CViewItemsWalkerNodePos& walkerPos )
{
    walkerPos = m_pSession->Items().end();
    return walkerPos.Valid();
}


/**
 *
 */
const CViewItemsSessionWalkerNode& CViewItemsSessionWalkerNode::operator = (const CViewItemsSessionWalkerNode& node)
{
    if ( this == &node )
        return *this;

    m_pSession = node.m_pSession;

    return *this;
}

