#ifndef __VIEWITEMSWALKER_HPP__
#define __VIEWITEMSWALKER_HPP__

#include "IViewItemsWalkerMethods.hpp"
#include "ViewItemsModuleWalkerNode.hpp"
#include "ViewItemsWalkerPos.hpp"
#include <vector>


class CModuleViewItems;
class CSessionViewItems;
class CViewItemsModulesMgr;


/**
 *
 */
class CViewItemsWalkerCore : public IViewItemsWalkerMethods
{
public:
    CViewItemsWalkerCore(CViewItemsModulesMgr& rViewItemsModulesMgr);
    explicit CViewItemsWalkerCore(const CViewItemsWalkerCore& walker);
    virtual ~CViewItemsWalkerCore();

    virtual void OnNewModuleViewItem( CModuleViewItems* pModule );
    virtual void OnNewSessionViewItem( CModuleViewItems* pModule, CSessionViewItems* pSession );
    virtual void OnNewViewItem( CViewItem* pViewItem );
    virtual void OnItemWidthChanged( CViewItem* pViewItem );

    virtual bool InitNewModulesPosition();

    virtual bool MoveToBegin();
    virtual bool MoveToNext();
    virtual bool MoveToPrevious();
    virtual bool MoveTo(const float& y);
    virtual bool MoveToLine(size_t lineNo);

    virtual bool ValidPos() const;
    virtual CViewItem* Item() const;
    virtual const float& ItemYPos() const;
    virtual const size_t LineNo() const;
    virtual const size_t LineNumber() const;

    virtual void PushState();
    virtual void PopState();

    virtual void Clone( const CViewItemsWalkerCore& walker );
//    const CViewItemsWalkerCore& operator = (const CViewItemsWalkerCore& walker);

    virtual const float& Height() const;
    virtual const float& Width() const;

    virtual void Lock();
    virtual void Unlock();

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
    void InitFromModulesMgr();

    bool Locked() const     { return m_LockedCount > 0; }

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

    int                                     m_LockedCount;
};

#endif // VIEWITEMSWALKER_HPP
