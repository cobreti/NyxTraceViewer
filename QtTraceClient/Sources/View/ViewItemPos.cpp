#include "ViewItemPos.hpp"
#include "ViewItem.hpp"

/**
 *
 */
CViewItemPos::CViewItemPos() :
    m_pList(NULL)
{
}


/**
 *
 */
CViewItemPos::CViewItemPos( const TViewItemsList& rList, const TViewItemsList::const_iterator& pos) :
    m_pList(&rList),
    m_Pos(pos)
{
}


/**
 *
 */
CViewItemPos::CViewItemPos(const CViewItemPos &rPos) :
    m_Pos(rPos.m_Pos),
    m_pList(rPos.m_pList)
{
}


/**
 *
 */
CViewItemPos::~CViewItemPos()
{
}


/**
 *
 */
const CViewItemPos& CViewItemPos::operator = (const CViewItemPos& pos)
{
    if ( &pos != this )
    {
        m_pList = pos.m_pList;
        m_Pos = pos.m_Pos;
    }

    return *this;
}


/**
 *
 */
bool CViewItemPos::MoveToNext()
{
    if ( m_Pos == m_pList->end() )
        return false;

    ++ m_Pos;

    return true;
}


/**
 *
 */
bool CViewItemPos::MoveToPrevious()
{
    if ( m_Pos == m_pList->begin())
        return false;

    -- m_Pos;

    return true;
}


/**
 *
 */
bool CViewItemPos::IsFirst() const
{
    if ( m_pList )
        return m_Pos == m_pList->begin();

    return false;
}


/**
 *
 */
bool CViewItemPos::IsLast() const
{
    if ( m_pList )
        return m_Pos == m_pList->end();

    return false;
}


/**
 *
 */
bool CViewItemPos::IsValid() const
{
    if ( m_pList )
        return m_Pos != m_pList->end();

    return false;
}


