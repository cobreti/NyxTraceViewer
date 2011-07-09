#include "ViewItemsModuleWalkerNode.hpp"
#include "ViewItemsSessionWalkernode.hpp"
#include "../ModuleViewItems.hpp"


/**
 *
 */
CViewItemsModuleWalkerNode::CViewItemsModuleWalkerNode(CModuleViewItems* pModuleViewItems) :
    CViewItemsWalkerNode(),
    m_pModuleViewItems(pModuleViewItems)
{
    m_CachedPos.Module() = this;
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
    if ( m_ChildNodes.empty() )
        return false;

    CViewItemsSessionWalkerNode*        pNode = m_ChildNodes[0];

    return pNode->GetTopPos(m_CachedPos);
}


/**
 *
 */
bool CViewItemsModuleWalkerNode::MoveToNext()
{
    if ( !m_CachedPos.Valid() )
        return false;

    if ( !m_CachedPos.ItemPos().MoveToNext() )
    {
        CViewItemsSessionWalkerNode*        pNextSession = GetNextSession(m_CachedPos.Session());
        if ( pNextSession )
            return pNextSession->GetTopPos(m_CachedPos);
        return false;
    }

    return true;
}


/**
 *
 */
bool CViewItemsModuleWalkerNode::MoveToPrevious()
{
    if ( !m_CachedPos.Valid() )
        return false;

    if ( !m_CachedPos.ItemPos().MoveToPrevious() )
    {
        CViewItemsSessionWalkerNode*        pPreviousSession = GetPreviousSession(m_CachedPos.Session());
        if ( pPreviousSession )
            return pPreviousSession->GetLastPos(m_CachedPos);
        return false;
    }

    return true;
}


/**
 *
 */
void CViewItemsModuleWalkerNode::GetPosData( CViewItemsWalkerPos& walkerPos ) const
{
    walkerPos.ItemPos() = m_CachedPos.ItemPos();
    walkerPos.Module() = m_CachedPos.Module();
    walkerPos.Session() = m_CachedPos.Session();
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
    m_PositionStack.push_back(m_CachedPos);
}


/**
 *
 */
void CViewItemsModuleWalkerNode::PopState()
{
    if ( !m_PositionStack.empty())
    {
        m_CachedPos = m_PositionStack.back();
        m_PositionStack.pop_back();
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

    m_CachedPos = node.m_CachedPos;
    m_CachedPos.Module() = this;

    for (size_t index = 0; index < node.m_ChildNodes.size(); ++index)
    {
        m_ChildNodes[index] = new CViewItemsSessionWalkerNode(*node.m_ChildNodes[index]);

        if ( node.m_ChildNodes[index] == m_CachedPos.Session() )
            m_CachedPos.Session() = m_ChildNodes[index];
    }
}

