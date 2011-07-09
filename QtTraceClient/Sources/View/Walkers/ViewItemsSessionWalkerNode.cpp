#include "ViewItemsSessionWalkerNode.hpp"
#include "ViewItemsWalkerPos.hpp"
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
bool CViewItemsSessionWalkerNode::GetTopPos( CViewItemsWalkerPos& walkerPos )
{
    walkerPos.ItemPos() = m_pSession->Items().begin();
    walkerPos.Session() = this;

    return walkerPos.ItemPos().IsValid();
}


/**
 *
 */
bool CViewItemsSessionWalkerNode::GetLastPos( CViewItemsWalkerPos& walkerPos )
{
    walkerPos.ItemPos() = m_pSession->Items().end();
    walkerPos.Session() = this;

    return walkerPos.ItemPos().IsValid();
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

