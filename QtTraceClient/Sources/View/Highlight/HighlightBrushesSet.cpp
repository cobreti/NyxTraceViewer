#include "HighlightBrushesSet.hpp"
#include "HighlightBrush.hpp"


/**
 *
 */
CHighlightBrushesSet::CHighlightBrushesSet()
{
    m_Brushes.resize(10);
    for (size_t index = 0; index < m_Brushes.size(); ++index)
        m_Brushes[index] = new CHighlightBrush();
}


/**
 *
 */
CHighlightBrushesSet::~CHighlightBrushesSet()
{
    for (size_t index = 0; index < m_Brushes.size(); ++index)
        delete m_Brushes[index];
}

