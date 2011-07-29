#include "ViewDrawSettings.hpp"
#include "View/ViewItemPainter.hpp"


/**
 *
 */
CViewDrawSettings::CViewDrawSettings() :
    m_LineHeight(0)
{
    m_Painters.resize( CViewItemPainter::ePId_Count );

    for (size_t index = 0; index < m_Painters.size(); ++index )
        m_Painters[index] = NULL;
}


/**
 *
 */
CViewDrawSettings::~CViewDrawSettings()
{
}


/**
 *
 */
void CViewDrawSettings::CalculateLineHeight()
{
    for (size_t index = 0; index < m_Painters.size(); ++index)
    {
        if ( m_Painters[index] )
            m_LineHeight = Nyx::Max(m_LineHeight, m_Painters[index]->MaxFontHeight());
    }
}


