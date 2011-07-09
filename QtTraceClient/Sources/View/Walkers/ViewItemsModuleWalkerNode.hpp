#ifndef __VIEWITEMSMODULEWALKERNODE_HPP__
#define __VIEWITEMSMODULEWALKERNODE_HPP__

#include <Nyx.hpp>

#include "ViewItemsWalkerNodesPool.hpp"
#include "ViewItemsWalkerNode.hpp"
#include "ViewItemsWalkerPos.hpp"
#include "ViewItemsSessionWalkerNode.hpp"


class CModuleViewItems;
class CViewItemsModuleWalkerNode;


/**
 *
 */
class CViewItemsModuleWalkerNode : public CViewItemsWalkerNode
{
public:
    CViewItemsModuleWalkerNode(CModuleViewItems* pModuleViewItems);
    virtual ~CViewItemsModuleWalkerNode();

    bool ContainsModule( CModuleViewItems* pModule ) const;
    void AddNode( CViewItemsSessionWalkerNode* pNode );

    bool MoveToBegin();
    bool MoveToNext();
    bool MoveToPrevious();

    void GetPosData( CViewItemsWalkerPos& walkerPos ) const;

    const CViewItemsWalkerPos& CachedPos() const            { return m_CachedPos; }

    const Nyx::CWString& Name() const;

    void PushState();
    void PopState();

protected:

    typedef         std::vector<CViewItemsWalkerPos>        TWalkerPosStack;

protected:

    CViewItemsSessionWalkerNode* GetNextSession( CViewItemsSessionWalkerNode* pSession ) const;
    CViewItemsSessionWalkerNode* GetPreviousSession( CViewItemsSessionWalkerNode* pSession ) const;

protected:

    CModuleViewItems*                       m_pModuleViewItems;
    TViewItemsSessionWalkerNodeArray        m_ChildNodes;

    CViewItemsWalkerPos                     m_CachedPos;

    TWalkerPosStack                         m_PositionStack;
};

#endif // VIEWITEMSMODULEWALKERNODE_HPP

