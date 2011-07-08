#ifndef __VIEWITEMSWALKER_HPP__
#define __VIEWITEMSWALKER_HPP__

#include "ViewItemsModuleWalkerNode.hpp"
#include "ViewItemsWalkerPos.hpp"
#include <vector>


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

    bool InitNewModulesPosition();

    bool MoveToBegin();
    bool MoveToNext();
    bool MoveToPrevious();
    bool MoveTo(const float& y);

    bool ValidPos() const                   { return m_Pos.Valid(); }
    const CViewItemPos& ItemPos() const     { return m_Pos.ItemPos(); }
    const float& ItemYPos() const           { return m_Pos.Y(); }

protected:

    typedef     std::vector<CViewItemsModuleWalkerNode*>        ViewItemsModuleWalkerNodeArray;

    enum EDirection
    {
        eD_Undefined,
        eD_Increasing,
        eD_Decreasing
    };

protected:

    CViewItemsModuleWalkerNode* GetNodeWithModule( CModuleViewItems* pModule ) const;

protected:

    ViewItemsModuleWalkerNodeArray          m_Nodes;
    CViewItemsWalkerPos                     m_Pos;
    EDirection                              m_Direction;
};

#endif // VIEWITEMSWALKER_HPP
