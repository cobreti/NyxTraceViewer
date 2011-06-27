#include "ViewItemPos.hpp"
#include "ViewItem.hpp"

/**
 *
 */
CViewItemPos::CViewItemPos() :
m_pData(NULL)
{
}


/**
 *
 */
CViewItemPos::CViewItemPos(const CViewItemPos &rPos)
{
    m_pData = rPos.m_pData->Clone();
}


/**
 *
 */
CViewItemPos::~CViewItemPos()
{
    delete m_pData;
}


/**
 *
 */
bool CViewItemPos::IsValid() const
{
    if ( m_pData )
        return m_pData->IsValid();

    return false;
}


/**
 *
 */
const CViewItemPos& CViewItemPos::operator = (const CViewItemPos& pos)
{
    if ( &pos != this )
    {
        if ( m_pData )
        {
            delete m_pData;
            m_pData = NULL;
        }

        if ( pos.m_pData )
            m_pData = pos.m_pData->Clone();
    }

    return *this;
}


/**
 *
 */
bool CViewItemPos::MoveTo(const float& y)
{
    while ( m_pData->IsValid() && m_pData->Y() + m_pData->Item()->GetSize().height() < y && m_pData->MoveToNext() );

    while ( m_pData->IsValid() && m_pData->Y() > y && m_pData->MoveToPrevious() );

    return ( m_pData->IsValid() && m_pData->Y() <= y && m_pData->Y() + m_pData->Item()->GetSize().height() >= y ); 
}

