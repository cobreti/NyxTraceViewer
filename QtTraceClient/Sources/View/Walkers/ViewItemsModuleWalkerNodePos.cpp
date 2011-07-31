#include "ViewItemsModuleWalkerNodePos.hpp"
#include "../ViewItem.hpp"


/**
 *
 */
CViewItemsModuleWalkerNodePos::CViewItemsModuleWalkerNodePos() : CViewItemsWalkerNodePos(),
    m_SessionNodeId(kInvalidNodeId)
{
}


/**
 *
 */
CViewItemsModuleWalkerNodePos::CViewItemsModuleWalkerNodePos(const CViewItemsModuleWalkerNodePos &pos) :
    CViewItemsWalkerNodePos(pos),
    m_SessionNodeId(pos.m_SessionNodeId)
{
}


/**
 *
 */
CViewItemsModuleWalkerNodePos::~CViewItemsModuleWalkerNodePos()
{
}


/**
 *
 */
const CViewItemsModuleWalkerNodePos& CViewItemsModuleWalkerNodePos::operator = (const CViewItemsModuleWalkerNodePos& pos)
{
    CViewItemsWalkerNodePos::operator = (pos);

    m_SessionNodeId = pos.m_SessionNodeId;

    return *this;
}


/**
 *
 */
bool CViewItemsModuleWalkerNodePos::Valid() const
{
    return CViewItemsWalkerNodePos::Valid() && (m_SessionNodeId != kInvalidNodeId );
}


/**
 *
 */
bool CViewItemsModuleWalkerNodePos::IsBefore( const CViewItemsModuleWalkerNodePos& pos ) const
{
    return m_ItemPos.Item()->TickCount() < pos.Item()->TickCount();
}


/**
 *
 */
bool CViewItemsModuleWalkerNodePos::IsAfter( const CViewItemsModuleWalkerNodePos& pos ) const
{
    return m_ItemPos.Item()->TickCount() > pos.Item()->TickCount();
}


/**
 *
 */
bool CViewItemsModuleWalkerNodePos::IsConcurrent( const CViewItemsModuleWalkerNodePos& pos) const
{
    return m_ItemPos.Item()->TickCount() == pos.Item()->TickCount() && m_ItemPos.Item()->Id() != pos.Item()->Id();
}


ViewItemID CViewItemsModuleWalkerNodePos::ItemId() const
{
    if ( m_ItemPos.Item() )
        return m_ItemPos.Item()->Id();

    return 0;
}
