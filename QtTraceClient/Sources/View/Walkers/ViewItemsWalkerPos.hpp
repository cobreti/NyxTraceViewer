#ifndef _VIEWITEMSWALKERPOS_HPP_
#define _VIEWITEMSWALKERPOS_HPP_

#include <Nyx.hpp>
#include "../ViewItemPos.hpp"


class CViewItemsSessionWalkerNode;
class CViewItemsModuleWalkerNode;


/**
 *
 */
class CViewItemsWalkerPos
{
public:
    CViewItemsWalkerPos();
    CViewItemsWalkerPos(const CViewItemsWalkerPos& pos);
    ~CViewItemsWalkerPos();

    const CViewItemPos&             ItemPos() const             { return m_ItemPos; }
    CViewItemPos&                   ItemPos()                   { return m_ItemPos; }

    CViewItemsModuleWalkerNode*     Module() const              { return m_pModule; }
    CViewItemsModuleWalkerNode*&    Module()                    { return m_pModule; }

    CViewItemsSessionWalkerNode*    Session() const             { return m_pSession; }
    CViewItemsSessionWalkerNode*&   Session()                   { return m_pSession; }

    const float&                    Y() const                   { return m_Y; }
    float&                          Y()                         { return m_Y; }

    const CViewItemsWalkerPos& operator = (const CViewItemsWalkerPos& pos);
    bool operator < (const CViewItemsWalkerPos& pos) const;

    bool Valid() const;

protected:

    CViewItemPos                    m_ItemPos;
    CViewItemsModuleWalkerNode*     m_pModule;
    CViewItemsSessionWalkerNode*    m_pSession;
    float                           m_Y;
};

#endif // VIEWITEMSWALKERPOS_HPP
