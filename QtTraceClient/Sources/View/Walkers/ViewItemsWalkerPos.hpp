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

    size_t                          LineNo() const                      { return m_LineNo; }
    size_t&                         LineNo()                            { return m_LineNo; }

    const CViewItemsWalkerPos& operator = (const CViewItemsWalkerPos& pos);
    const CViewItemsWalkerPos& operator = (const CViewItemsModuleWalkerNodePos& pos);

    bool Valid() const;

protected:


    ViewItemsNodeId                 m_ModuleNodeId;
    size_t                          m_LineNo;
};

#endif // VIEWITEMSWALKERPOS_HPP
