#ifndef __VIEWITEMSWALKERNODE_HPP__
#define __VIEWITEMSWALKERNODE_HPP__

#include <Nyx.hpp>

#include "ViewItemsWalkerStats.hpp"


class CModuleViewItems;
class CViewItemsWalkerPos;


/**
 *
 */
class CViewItemsWalkerNode
{
public:
    CViewItemsWalkerNode();
    virtual ~CViewItemsWalkerNode();

    const CViewItemsWalkerStats&        Stats() const       { return m_Stats; }
    CViewItemsWalkerStats&              Stats()             { return m_Stats; }

protected:

    CViewItemsWalkerStats               m_Stats;
};




#endif // VIEWITEMSWALKERNODE_HPP
