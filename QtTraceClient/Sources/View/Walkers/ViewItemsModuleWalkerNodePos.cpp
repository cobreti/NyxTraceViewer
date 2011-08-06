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
    return (m_SessionNodeId != kInvalidNodeId ) && CViewItemsWalkerNodePos::Valid();
}




ViewItemID CViewItemsModuleWalkerNodePos::ItemId() const
{
    if ( m_ItemPos.Item() )
        return m_ItemPos.Item()->Id();

    return 0;
}
