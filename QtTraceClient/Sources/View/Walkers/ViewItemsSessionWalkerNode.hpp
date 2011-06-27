#ifndef __VIEWITEMSSESSIONWALKERNODE_HPP__
#define __VIEWITEMSSESSIONWALKERNODE_HPP__

#include <Nyx.hpp>
#include "ViewItemsWalkerNode.hpp"
#include "ViewItemsWalkerNodesPool.hpp"


class CSessionViewItems;
class CViewItemsSessionWalkerNode;
class CViewItemPos;

/**
 *
 */
typedef     std::list<CViewItemsSessionWalkerNode*, Nyx::StdListAllocator<CViewItemsSessionWalkerNode*, CViewItemsWalkerNodesPool> >       TViewItemsSessionWalkerNodeList;


/**
 *
 */
class CViewItemsSessionWalkerNode : public CViewItemsWalkerNode
{
public:
    CViewItemsSessionWalkerNode(CSessionViewItems* pSession);
    virtual ~CViewItemsSessionWalkerNode();

    virtual bool ContainsModule( CModuleViewItems* pModule ) const { return false; }

    virtual bool GetTopPos( CViewItemsWalkerPos& walkerPos );
    virtual bool GetLastPos( CViewItemsWalkerPos& walkerPos );

protected:

    CSessionViewItems*      m_pSession;
};

#endif // VIEWITEMSSESSIONWALKERNODE_HPP
