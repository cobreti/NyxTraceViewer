#ifndef __VIEWITEMSWALKER_HPP__
#define __VIEWITEMSWALKER_HPP__

#include "ViewItemsModuleWalkerNode.hpp"
#include "ViewItemsWalkerPos.hpp"

class CModuleViewItems;
class CSessionViewItems;

/**
 *
 */
class CViewItemsWalker
{
public:
    CViewItemsWalker();
    virtual ~CViewItemsWalker();

    void OnNewModuleViewItem( CModuleViewItems* pModule );
    void OnNewSessionViewItem( CModuleViewItems* pModule, CSessionViewItems* pSession );

    bool MoveToBegin();
    bool MoveToNext();
    bool MoveToPrevious();
    bool MoveTo(const float& y);

    bool ValidPos() const                   { return m_Pos.Valid(); }
    const CViewItemPos& ItemPos() const     { return m_Pos.ItemPos(); }
    const float& ItemYPos() const           { return m_Pos.Y(); }

protected:

    CViewItemsModuleWalkerNode* GetNodeWithModule( CModuleViewItems* pModule ) const;

protected:

    TViewItemsModuleWalkerNodeList          m_Nodes;
    CViewItemsWalkerPos                     m_Pos;
};

#endif // VIEWITEMSWALKER_HPP
