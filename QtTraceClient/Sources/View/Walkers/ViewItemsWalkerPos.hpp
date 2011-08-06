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
//typedef     std::set<ViewItemID>            ViewItemIDSet;


/**
 *
 */
class CViewItemsWalkerPos : public CViewItemsModuleWalkerNodePos
{
public:
    CViewItemsWalkerPos();
    CViewItemsWalkerPos(const CViewItemsWalkerPos& pos);
    virtual ~CViewItemsWalkerPos();

    ViewItemsNodeId                     ModuleNodeId() const            { return m_ModuleNodeId; }
    ViewItemsNodeId&                    ModuleNodeId()                  { return m_ModuleNodeId; }

    const float&                    Y() const                           { return m_Y; }
    float&                          Y()                                 { return m_Y; }

    const CViewItemsWalkerPos& operator = (const CViewItemsWalkerPos& pos);
    const CViewItemsWalkerPos& operator = (const CViewItemsModuleWalkerNodePos& pos);

    bool Valid() const;

protected:


    ViewItemsNodeId                 m_ModuleNodeId;

    float                           m_Y;
};

#endif // VIEWITEMSWALKERPOS_HPP
