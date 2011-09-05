#include "ViewItemsWalkerPos.hpp"
#include "../ViewItem.hpp"


/**
 *
 */
CViewItemsWalkerPos::CViewItemsWalkerPos() :
    CViewItemsModuleWalkerNodePos(),
    m_ModuleNodeId(kInvalidNodeId),
    m_Y(0.0f)
{
}


/**
 *
 */
CViewItemsWalkerPos::CViewItemsWalkerPos(const CViewItemsWalkerPos &pos) :
    CViewItemsModuleWalkerNodePos(pos),
    m_ModuleNodeId(pos.m_ModuleNodeId),
    m_Y(pos.m_Y)
{
}


/**
 *
 */
CViewItemsWalkerPos::~CViewItemsWalkerPos()
{
}


/**
 *
 */
const CViewItemsWalkerPos& CViewItemsWalkerPos::operator = (const CViewItemsWalkerPos& pos)
{
    CViewItemsModuleWalkerNodePos::operator = (pos);

    m_ModuleNodeId = pos.m_ModuleNodeId;
    m_Y = pos.m_Y;

    return *this;
}


/**
 *
 */
const CViewItemsWalkerPos& CViewItemsWalkerPos::operator = (const CViewItemsModuleWalkerNodePos& pos)
{
    CViewItemsModuleWalkerNodePos::operator = (pos);
    return *this;
}


/**
 *
 */
bool CViewItemsWalkerPos::Valid() const
{
    return m_SessionNodeId != kInvalidNodeId && m_ModuleNodeId != kInvalidNodeId && m_ItemPos.IsValid();
}
