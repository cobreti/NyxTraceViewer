#include "ViewItemsWalkerPos.hpp"
#include "../ViewItem.hpp"


/**
 *
 */
CViewItemsWalkerPos::CViewItemsWalkerPos() :
    m_pModule(NULL),
    m_pSession(NULL),
    m_Y(0.0f)
{
}


/**
 *
 */
CViewItemsWalkerPos::CViewItemsWalkerPos(const CViewItemsWalkerPos &pos) :
    m_ItemPos(pos.m_ItemPos),
    m_pModule(pos.m_pModule),
    m_pSession(pos.m_pSession),
    m_Y(pos.m_Y),
    m_ConcurrentItemsVisited(pos.m_ConcurrentItemsVisited)
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
    m_ItemPos = pos.m_ItemPos;
    m_pModule = pos.m_pModule;
    m_pSession = pos.m_pSession;
    m_Y = pos.m_Y;
    m_ConcurrentItemsVisited = pos.m_ConcurrentItemsVisited;

    return *this;
}


/**
 *
 */
//bool CViewItemsWalkerPos::operator < (const CViewItemsWalkerPos& pos) const
//{
//    return (m_ItemPos.Item()->TickCount() < pos.m_ItemPos.Item()->TickCount());/* ||
//           (m_ItemPos.Item()->TickCount() == pos.m_ItemPos.Item()->TickCount());*/
//}


/**
 *
 */
//bool CViewItemsWalkerPos::operator <= (const CViewItemsWalkerPos& pos) const
//{
//    return (m_ItemPos.Item()->TickCount() < pos.m_ItemPos.Item()->TickCount()) ||
//           (m_ItemPos.Item()->TickCount() == pos.m_ItemPos.Item()->TickCount());
//}


/**
 *
 */
bool CViewItemsWalkerPos::IsBefore( const CViewItemsWalkerPos& pos ) const
{
    return m_ItemPos.Item()->TickCount() < pos.ItemPos().Item()->TickCount();
}


/**
 *
 */
bool CViewItemsWalkerPos::IsAfter( const CViewItemsWalkerPos& pos ) const
{
    return m_ItemPos.Item()->TickCount() > pos.ItemPos().Item()->TickCount();
}


/**
 *
 */
bool CViewItemsWalkerPos::IsConcurrent( const CViewItemsWalkerPos& pos) const
{
    return m_ItemPos.Item()->TickCount() == pos.ItemPos().Item()->TickCount() && m_ItemPos.Item()->Id() != pos.ItemPos().Item()->Id();
}


/**
 *
 */
bool CViewItemsWalkerPos::Valid() const
{
    return ( m_ItemPos.IsValid() && m_pSession != NULL && m_pModule != NULL);
}

