#ifndef __VIEWITEMSMODULEWALKERNODE_HPP__
#define __VIEWITEMSMODULEWALKERNODE_HPP__

#include <Nyx.hpp>

#include "ViewItemsWalkerNodesPool.hpp"
#include "ViewItemsWalkerNode.hpp"
#include "ViewItemsModuleWalkerNodePos.hpp"
#include "ViewItemsSessionWalkerNode.hpp"


class CModuleViewItems;
class CViewItemsModuleWalkerNode;
class CViewItemsWalkerPos;


/**
 *
 */
enum EViewItemsModuleWalkerNodeState
{
    eVIMWNS_Unitinialized,
    eVIMWNS_BeforeFirst,
    eVIMWNS_AfterLast,
    eVIMWNS_ValidPos
};


/**
 *
 */
class CViewItemsModuleWalkerNode : public CViewItemsWalkerNode
{
public:
    CViewItemsModuleWalkerNode(CModuleViewItems* pModuleViewItems);
    explicit CViewItemsModuleWalkerNode(const CViewItemsModuleWalkerNode& node);
    virtual ~CViewItemsModuleWalkerNode();

    void InitModulePosition();
    void RefreshPositions();

    bool ContainsModule( CModuleViewItems* pModule ) const;
    void AddNode( CViewItemsSessionWalkerNode* pNode );

    bool MoveToBegin();
    bool MoveToNext();
    bool MoveToPrevious();
    bool ValidPos() const;

    const CViewItemsModuleWalkerNodePos& LowerPos() const           { return m_LowerPos; }
    const CViewItemsModuleWalkerNodePos& UpperPos() const           { return m_UpperPos; }

    const Nyx::CWString& Name() const;

    EViewItemsModuleWalkerNodeState     State() const       { return m_State; }

    void PushState();
    void PopState();

    CViewItemsSessionWalkerNode* GetEquivalentSession( CViewItemsModuleWalkerNode* pModuleNode, CViewItemsSessionWalkerNode* pSessionNode );

    const CViewItemsModuleWalkerNode& operator = (const CViewItemsModuleWalkerNode& node);

protected:

    typedef         std::vector<CViewItemsModuleWalkerNodePos>        TWalkerPosStack;

protected:

    CViewItemsSessionWalkerNode* GetNextSession( CViewItemsSessionWalkerNode* pSession ) const;
    CViewItemsSessionWalkerNode* GetPreviousSession( CViewItemsSessionWalkerNode* pSession ) const;

    void ClearChildNodes();
    void CopyDataFrom( const CViewItemsModuleWalkerNode& node);

    void MoveToNext( CViewItemsModuleWalkerNodePos& pos );
    void MoveToPrevious( CViewItemsModuleWalkerNodePos& pos );
    void MoveToBegin( CViewItemsModuleWalkerNodePos& pos );

    void InitFromViewItems();

protected:

    CModuleViewItems*                       m_pModuleViewItems;
    TViewItemsSessionWalkerNodeArray        m_ChildNodes;

    CViewItemsModuleWalkerNodePos           m_LowerPos;
    CViewItemsModuleWalkerNodePos           m_UpperPos;

    TWalkerPosStack                         m_LowerPosStack;
    TWalkerPosStack                         m_UpperPosStack;

    EViewItemsModuleWalkerNodeState         m_State;
};

#endif // VIEWITEMSMODULEWALKERNODE_HPP

