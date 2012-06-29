#include "HighlightBrush.hpp"


/**
 *
 */
CHighlightBrush::CHighlightBrush()
{
    SetColor( Qt::GlobalColor::yellow );
}


/**
 *
 */
CHighlightBrush::~CHighlightBrush()
{
}


/**
 *
 */
void CHighlightBrush::SetColor(const QColor& color)
{
    m_Color = color;
    m_Brush = QBrush(color);
}