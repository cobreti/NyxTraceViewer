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

