#ifndef _VIEWITEMSWALKERPOS_HPP_
#define _VIEWITEMSWALKERPOS_HPP_

#include <Nyx.hpp>
#include "../ViewItemPos.hpp"
#include "../ViewItem.hpp"

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
class CViewItemsWalkerPos
{
public:
    CViewItemsWalkerPos();
    CViewItemsWalkerPos(const CViewItemsWalkerPos& pos);
    ~CViewItemsWalkerPos();

    const CViewItemPos&             ItemPos() const                     { return m_ItemPos; }
    CViewItemPos&                   ItemPos()                           { return m_ItemPos; }

    ViewItemID                      ItemId() const                      { return m_ItemPos.Item()->Id(); }

    CViewItemsModuleWalkerNode*     Module() const                      { return m_pModule; }
    CViewItemsModuleWalkerNode*&    Module()                            { return m_pModule; }

    CViewItemsSessionWalkerNode*    Session() const                     { return m_pSession; }
    CViewItemsSessionWalkerNode*&   Session()                           { return m_pSession; }

    const float&                    Y() const                           { return m_Y; }
    float&                          Y()                                 { return m_Y; }

    const ViewItemIDSet&            ConcurrentItemsVisited() const      { return m_ConcurrentItemsVisited; }
    ViewItemIDSet&                  ConcurrentItemsVisited()            { return m_ConcurrentItemsVisited; }

    const CViewItemsWalkerPos& operator = (const CViewItemsWalkerPos& pos);
//    bool operator < (const CViewItemsWalkerPos& pos) const;
//    bool operator <= (const CViewItemsWalkerPos& pos) const;

    bool IsBefore( const CViewItemsWalkerPos& pos ) const;
    bool IsAfter( const CViewItemsWalkerPos& pos ) const;
    bool IsConcurrent( const CViewItemsWalkerPos& pos) const;

    bool Valid() const;

protected:

    CViewItemPos                    m_ItemPos;
    CViewItemsModuleWalkerNode*     m_pModule;
    CViewItemsSessionWalkerNode*    m_pSession;
    float                           m_Y;
    ViewItemIDSet                   m_ConcurrentItemsVisited;
};

#endif // VIEWITEMSWALKERPOS_HPP
