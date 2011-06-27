#include "ViewItemsWalkerStats.hpp"


/**
 *
 */
CViewItemsWalkerStats::CViewItemsWalkerStats() :
m_ItemsCount(0)
{
}


/**
 *
 */
CViewItemsWalkerStats::CViewItemsWalkerStats(const CViewItemsWalkerStats& stats) :
    m_ItemsCount(stats.m_ItemsCount),
    m_Size(stats.m_Size),
    m_MaxLineSize(stats.m_MaxLineSize)
{
}


/**
 *
 */
CViewItemsWalkerStats::~CViewItemsWalkerStats()
{
}


/**
 *
 */
const CViewItemsWalkerStats& CViewItemsWalkerStats::operator = (const CViewItemsWalkerStats& stats)
{
    m_ItemsCount = stats.m_ItemsCount;
    m_Size = stats.m_Size;
    m_MaxLineSize = stats.m_MaxLineSize;

    return *this;
}


/**
 *
 */
void CViewItemsWalkerStats::Add( CViewItemsWalkerStats& stats )
{
    m_ItemsCount += stats.m_ItemsCount;

    if ( stats.m_MaxLineSize.height() > m_MaxLineSize.height() )
        m_MaxLineSize.setHeight(stats.m_MaxLineSize.height());

    if ( stats.m_MaxLineSize.width() > m_MaxLineSize.width() )
        m_MaxLineSize.setWidth(stats.m_MaxLineSize.width());

    if ( stats.m_Size.width() > m_Size.width() )
        m_Size.setWidth( stats.m_Size.width() );

    if ( stats.m_Size.height() > m_Size.height() )
        m_Size.setHeight( stats.m_Size.height());
}
