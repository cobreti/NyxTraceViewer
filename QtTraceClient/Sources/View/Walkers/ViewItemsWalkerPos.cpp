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
    m_ItemPos = pos.m_ItemPos;
    m_pModule = pos.m_pModule;
    m_pSession = pos.m_pSession;
    m_Y = pos.m_Y;

    return *this;
}


/**
 *
 */
bool CViewItemsWalkerPos::operator < (const CViewItemsWalkerPos& pos) const
{
    return (m_ItemPos.Item()->TickCount() < pos.m_ItemPos.Item()->TickCount()) ||
           (m_ItemPos.Item()->TickCount() == pos.m_ItemPos.Item()->TickCount());
}


/**
 *
 */
bool CViewItemsWalkerPos::Valid() const
{
    return ( m_ItemPos.IsValid() && m_pSession != NULL && m_pModule != NULL);
}

