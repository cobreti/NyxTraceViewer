#ifndef __VIEWITEMSSESSIONWALKERNODE_HPP__
#define __VIEWITEMSSESSIONWALKERNODE_HPP__

#include <Nyx.hpp>
#include "ViewItemsWalkerNode.hpp"
#include "ViewItemsWalkerNodesPool.hpp"
#include <vector>

class CSessionViewItems;
class CViewItemsSessionWalkerNode;
class CViewItemPos;
class CViewItemsWalkerNodePos;

/**
 *
 */
typedef     std::vector<CViewItemsSessionWalkerNode*>       TViewItemsSessionWalkerNodeArray;

/**
 *
 */
class CViewItemsSessionWalkerNode : public CViewItemsWalkerNode
{
public:
    CViewItemsSessionWalkerNode(CSessionViewItems* pSession);
    explicit CViewItemsSessionWalkerNode(const CViewItemsSessionWalkerNode& node);
    virtual ~CViewItemsSessionWalkerNode();

    virtual bool GetTopPos( CViewItemsWalkerNodePos& walkerPos );
    virtual bool GetLastPos( CViewItemsWalkerNodePos& walkerPos );

    const CViewItemsSessionWalkerNode& operator = (const CViewItemsSessionWalkerNode& node);

protected:

    CSessionViewItems*      m_pSession;
};

#endif // VIEWITEMSSESSIONWALKERNODE_HPP
