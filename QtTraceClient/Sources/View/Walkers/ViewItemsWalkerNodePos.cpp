#include "ViewItemsWalkerNodePos.hpp"
#include "../ViewItem.hpp"


/**
 *
 */
CViewItemsWalkerNodePos::CViewItemsWalkerNodePos()
{
}


/**
 *
 */
CViewItemsWalkerNodePos::CViewItemsWalkerNodePos(const CViewItemsWalkerNodePos &pos) :
    m_ItemPos(pos.m_ItemPos)
{
}


/**
 *
 */
CViewItemsWalkerNodePos::~CViewItemsWalkerNodePos()
{
}


/**
 *
 */
const CViewItemsWalkerNodePos& CViewItemsWalkerNodePos::operator = (const CViewItemsWalkerNodePos& pos)
{
    m_ItemPos = pos.m_ItemPos;

    return *this;
}


/**
 *
 */
const CViewItemsWalkerNodePos& CViewItemsWalkerNodePos::operator = (const CViewItemPos& pos)
{
    m_ItemPos = pos;
}


/**
 *
 */
bool CViewItemsWalkerNodePos::Valid() const
{
    return m_ItemPos.IsValid();
}


/**
 *
 */
bool CViewItemsWalkerNodePos::MoveToNext()
{
    return m_ItemPos.MoveToNext();
}


/**
 *
 */
bool CViewItemsWalkerNodePos::MoveToPrevious()
{
    return m_ItemPos.MoveToPrevious();
}


/**
 *
 */
bool CViewItemsWalkerNodePos::IsBefore( const CViewItemsWalkerNodePos& pos ) const
{
    return m_ItemPos.Item()->TickCount() < pos.Item()->TickCount();
}


/**
 *
 */
bool CViewItemsWalkerNodePos::IsAfter( const CViewItemsWalkerNodePos& pos ) const
{
    return m_ItemPos.Item()->TickCount() > pos.Item()->TickCount();
}


/**
 *
 */
bool CViewItemsWalkerNodePos::IsConcurrent( const CViewItemsWalkerNodePos& pos) const
{
    return m_ItemPos.Item()->TickCount() == pos.Item()->TickCount() && m_ItemPos.Item()->Id() != pos.Item()->Id();
}
