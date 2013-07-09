#include "ViewItemsModuleWalkerNode.hpp"
#include "ViewItemsSessionWalkerNode.hpp"
#include "ViewItemsWalkerPos.hpp"
#include "../ModuleViewItems.hpp"


/**
 *
 */
CViewItemsModuleWalkerNode::CViewItemsModuleWalkerNode(CModuleViewItems* pModuleViewItems) :
    CViewItemsWalkerNode(),
    m_pModuleViewItems(pModuleViewItems),
    m_State(eVIMWNS_Unitinialized)
{
    InitFromViewItems();
}


/**
 *
 */
CViewItemsModuleWalkerNode::CViewItemsModuleWalkerNode(const CViewItemsModuleWalkerNode& node) :
    CViewItemsWalkerNode(),
    m_pModuleViewItems(node.m_pModuleViewItems)
{
    CopyDataFrom(node);
}


/**
 *
 */
CViewItemsModuleWalkerNode::~CViewItemsModuleWalkerNode()
{
    ClearChildNodes();
}


/**
 *
 */
void CViewItemsModuleWalkerNode::InitModulePosition()
{
    if ( !ValidPos() )
        MoveToBegin();
}


/**
 *
 */
void CViewItemsModuleWalkerNode::RefreshPositions()
{
    if ( m_LowerPos.Valid() && !m_UpperPos.Valid() )
    {
        m_UpperPos = m_LowerPos;
        MoveToNext(m_UpperPos);
    }

    if ( !m_LowerPos.Valid() && m_UpperPos.Valid() )
    {
        m_LowerPos = m_UpperPos;
        MoveToPrevious(m_LowerPos);
    }
}


/**
 *
 */
bool CViewItemsModuleWalkerNode::ContainsModule( CModuleViewItems* pModule ) const
{
    return (m_pModuleViewItems->Name() == pModule->Name());
}


/**
 *
 */
void CViewItemsModuleWalkerNode::AddNode( CViewItemsSessionWalkerNode* pNode )
{
    m_ChildNodes.push_back(pNode);
}


/**
 *
 */
bool CViewItemsModuleWalkerNode::MoveToBegin()
{
    m_LowerPos.SessionNodeId() = kInvalidNodeId;

    MoveToBegin(m_UpperPos);

    return m_UpperPos.Valid();
}


/**
 *
 */
bool CViewItemsModuleWalkerNode::MoveToNext()
{
    if ( !m_UpperPos.Valid() )
    {
        CViewItemsModuleWalkerNodePos       pos(m_LowerPos);

        if ( pos.MoveToNext() )
            m_UpperPos = pos;
    }

    if ( m_UpperPos.Valid() )
    {
        m_LowerPos = m_UpperPos;
        MoveToNext(m_UpperPos);
        return true;
    }

    return false;
}


/**
 *
 */
bool CViewItemsModuleWalkerNode::MoveToPrevious()
{
    if ( m_LowerPos.Valid() )
    {
        m_UpperPos = m_LowerPos;
        MoveToPrevious(m_LowerPos);
    }

    return false;
}


/**
 *
 */
bool CViewItemsModuleWalkerNode::ValidPos() const
{
    return m_LowerPos.Valid() || m_UpperPos.Valid();
}


/**
 *
 */
const Nyx::CWString& CViewItemsModuleWalkerNode::Name() const
{
    return m_pModuleViewItems->Name();
}


/**
 *
 */
void CViewItemsModuleWalkerNode::PushState()
{
    m_LowerPosStack.push_back(m_LowerPos);
    m_UpperPosStack.push_back(m_UpperPos);
}


/**
 *
 */
void CViewItemsModuleWalkerNode::PopState()
{
    if ( !m_LowerPosStack.empty())
    {
        m_LowerPos = m_LowerPosStack.back();
        m_LowerPosStack.pop_back();
    }

    if ( !m_UpperPosStack.empty() )
    {
        m_UpperPos = m_UpperPosStack.back();
        m_UpperPosStack.pop_back();
    }
}


/**
 *
 */
CViewItemsSessionWalkerNode* CViewItemsModuleWalkerNode::GetEquivalentSession( CViewItemsModuleWalkerNode* pModuleNode, CViewItemsSessionWalkerNode* pSessionNode )
{
    for (size_t index = 0; index < pModuleNode->m_ChildNodes.size(); ++index)
        if ( pModuleNode->m_ChildNodes[index] == pSessionNode )
            return m_ChildNodes[index];

    return NULL;
}


/**
 *
 */
const CViewItemsModuleWalkerNode& CViewItemsModuleWalkerNode::operator = (const CViewItemsModuleWalkerNode& node)
{
    if ( this == &node )
        return *this;

    ClearChildNodes();
    CopyDataFrom(node);

    return *this;
}


/**
 *
 */
CViewItemsSessionWalkerNode* CViewItemsModuleWalkerNode::GetNextSession( CViewItemsSessionWalkerNode* pSession ) const
{
    CViewItemsSessionWalkerNode*            pNextSession = NULL;
    size_t                                  index;

    for (index = 0; index < m_ChildNodes.size()-1; ++index)
    {
        if ( m_ChildNodes[index] == pSession )
        {
            pNextSession = m_ChildNodes[index+1];
            break;
        }
    }

    return pNextSession;
}


/**
 *
 */
CViewItemsSessionWalkerNode* CViewItemsModuleWalkerNode::GetPreviousSession( CViewItemsSessionWalkerNode* pSession ) const
{
    CViewItemsSessionWalkerNode*        pPreviousSession = NULL;
    size_t                              index;

    for (index = 1; index < m_ChildNodes.size(); ++index)
    {
        if ( pSession == m_ChildNodes[index] )
        {
            pPreviousSession  =m_ChildNodes[index-1];
            break;
        }
    }

    return pPreviousSession;
}


/**
 *
 */
void CViewItemsModuleWalkerNode::ClearChildNodes()
{
    for (size_t index = 0; index < m_ChildNodes.size(); ++index)
        delete m_ChildNodes[index];
}


/**
 *
 */
void CViewItemsModuleWalkerNode::CopyDataFrom( const CViewItemsModuleWalkerNode& node)
{
    m_pModuleViewItems = node.m_pModuleViewItems;
    m_ChildNodes.resize(node.m_ChildNodes.size());

    m_LowerPos = node.m_LowerPos;
    m_UpperPos = node.m_UpperPos;

    for (size_t index = 0; index < node.m_ChildNodes.size(); ++index)
    {
        m_ChildNodes[index] = new CViewItemsSessionWalkerNode(*node.m_ChildNodes[index]);
    }
}


/**
 *
 */
void CViewItemsModuleWalkerNode::MoveToNext( CViewItemsModuleWalkerNodePos& pos )
{
    if ( !pos.Valid() )
        return;

    if ( !pos.MoveToNext() )
    {
        size_t      index = pos.SessionNodeId() + 1;
        pos.SessionNodeId() = kInvalidNodeId;
        if ( index < m_ChildNodes.size() )
        {
            CViewItemsSessionWalkerNode*        pSession = m_ChildNodes[index];
            if ( pSession->GetTopPos(pos) )
                pos.SessionNodeId() = index;
        }
    }
}


/**
 *
 */
void CViewItemsModuleWalkerNode::MoveToPrevious(CViewItemsModuleWalkerNodePos &pos)
{
    if ( !pos.Valid() )
        return;

    if ( !pos.MoveToPrevious() )
    {
        size_t index = pos.SessionNodeId() - 1;
        pos.SessionNodeId() = kInvalidNodeId;

        if ( index != kInvalidNodeId && index >= 0 && m_ChildNodes[index]->GetLastPos(pos))
            pos.SessionNodeId() = index;
    }
}


/**
 *
 */
void CViewItemsModuleWalkerNode::MoveToBegin( CViewItemsModuleWalkerNodePos& pos )
{
    pos.SessionNodeId() = kInvalidNodeId;

    if ( m_ChildNodes.empty() )
        return;

    CViewItemsSessionWalkerNode*        pNode = m_ChildNodes[0];

    if ( pNode->GetTopPos(pos) )
        pos.SessionNodeId() = 0;
}


/**
 *
 */
void CViewItemsModuleWalkerNode::InitFromViewItems()
{
    SessionViewItemsIDSet                   idsSet;
    SessionViewItemsIDSet::const_iterator   pos;

    m_pModuleViewItems->GetIDs(idsSet);

    pos = idsSet.begin();
    while ( pos != idsSet.end() )
    {
        CViewItemsSessionWalkerNode*        pSessionWalkerNode = new CViewItemsSessionWalkerNode(m_pModuleViewItems->Session(*pos));

        AddNode( pSessionWalkerNode );
        ++ pos;
    }
}
