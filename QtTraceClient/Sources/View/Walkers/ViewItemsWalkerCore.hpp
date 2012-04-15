#ifndef __VIEWITEMSWALKER_HPP__
#define __VIEWITEMSWALKER_HPP__

#include "ViewItemsModuleWalkerNode.hpp"
#include "ViewItemsWalkerPos.hpp"
#include <vector>


class CModuleViewItems;
class CSessionViewItems;
class CViewItemsModulesMgr;


/**
 *
 */
class CViewItemsWalkerCore
{
public:
    CViewItemsWalkerCore(CViewItemsModulesMgr& rViewItemsModulesMgr);
    explicit CViewItemsWalkerCore(const CViewItemsWalkerCore& walker);
    virtual ~CViewItemsWalkerCore();

    void OnNewModuleViewItem( CModuleViewItems* pModule );
    void OnNewSessionViewItem( CModuleViewItems* pModule, CSessionViewItems* pSession );
    void OnNewViewItem( CViewItem* pViewItem );
    void OnItemWidthChanged( CViewItem* pViewItem );

    bool InitNewModulesPosition();

    bool MoveToBegin();
    bool MoveToNext();
    bool MoveToPrevious();
    bool MoveTo(const float& y);

    bool ValidPos() const                   { return m_Pos.Valid(); }
    //const CViewItemPos& ItemPos() const     { return m_Pos.ItemPos(); }
    CViewItem* Item() const                 { return m_Pos.Item(); }
    const float& ItemYPos() const           { return m_Pos.Y(); }
    const size_t LineNumber() const         { return m_LineNumber; }

    void PushState();
    void PopState();

    const CViewItemsWalkerCore& operator = (const CViewItemsWalkerCore& walker);

    const float& Height() const     { return m_Height; }
    const float& Width() const      { return m_Width; }

protected:

    enum EDirection
    {
        eD_Undefined,
        eD_Increasing,
        eD_Decreasing
    };

    typedef     std::vector<CViewItemsModuleWalkerNode*>        ViewItemsModuleWalkerNodeArray;
    typedef     std::vector<CViewItemsWalkerPos>                TWalkerPosStack;
    typedef     std::vector<EDirection>                         TDirectionStack;
    typedef     std::vector<size_t>                             TLineNumberStack;

protected:

    CViewItemsModuleWalkerNode* GetNodeWithModule( CModuleViewItems* pModule ) const;
    void CopyDataFrom(const CViewItemsWalkerCore& walker);
    void ClearModuleNodes();

protected:

    ViewItemsModuleWalkerNodeArray          m_Nodes;

    CViewItemsWalkerPos                     m_Pos;
    EDirection                              m_Direction;
    size_t                                  m_LineNumber;

    TWalkerPosStack                         m_PositionStack;
    TDirectionStack                         m_DirectionStack;
    TLineNumberStack                        m_LineNumberStack;

    float                                   m_Height;
    float                                   m_Width;

    CViewItemsModulesMgr&                   m_rViewItemsModulesMgr;
};

#endif // VIEWITEMSWALKER_HPP
