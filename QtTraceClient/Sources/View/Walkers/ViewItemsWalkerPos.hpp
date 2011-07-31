#ifndef _VIEWITEMSWALKERPOS_HPP_
#define _VIEWITEMSWALKERPOS_HPP_

#include <Nyx.hpp>
#include "ViewItemsModuleWalkerNodePos.hpp"

#include <set>


class CViewItemsSessionWalkerNode;
class CViewItemsModuleWalkerNode;


/**
 *
 */
typedef     std::set<ViewItemID>            ViewItemIDSet;



/**
 *
 */
class CViewItemsWalkerPos : public CViewItemsModuleWalkerNodePos
{
public:
    CViewItemsWalkerPos();
    CViewItemsWalkerPos(const CViewItemsWalkerPos& pos);
    virtual ~CViewItemsWalkerPos();

    const CViewItemPos&             ItemPos() const                     { return m_ItemPos; }
    CViewItemPos&                   ItemPos()                           { return m_ItemPos; }

    ViewItemsNodeId                     ModuleNodeId() const            { return m_ModuleNodeId; }
    ViewItemsNodeId&                    ModuleNodeId()                  { return m_ModuleNodeId; }

    const float&                    Y() const                           { return m_Y; }
    float&                          Y()                                 { return m_Y; }

    const ViewItemIDSet&            ConcurrentItemsVisited() const      { return m_ConcurrentItemsVisited; }
    ViewItemIDSet&                  ConcurrentItemsVisited()            { return m_ConcurrentItemsVisited; }

    const CViewItemsWalkerPos& operator = (const CViewItemsWalkerPos& pos);
    const CViewItemsWalkerPos& operator = (const CViewItemsModuleWalkerNodePos& pos);

    bool Valid() const;

protected:

    ViewItemsNodeId                 m_ModuleNodeId;

    float                           m_Y;
    ViewItemIDSet                   m_ConcurrentItemsVisited;
};

#endif // VIEWITEMSWALKERPOS_HPP
