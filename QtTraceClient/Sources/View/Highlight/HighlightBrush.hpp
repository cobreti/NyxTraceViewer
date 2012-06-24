#ifndef _HIGHLIGHTBRUSH_HPP_
#define _HIGHLIGHTBRUSH_HPP_

#include <QColor>
#include <QBrush>

/**
 *
 */
class CHighlightBrush
{
public:
    CHighlightBrush();
    virtual ~CHighlightBrush();

    void SetColor( const QColor& color );
    const QColor& Color() const     { return m_Color; }

    const QBrush& Brush() const     { return m_Brush; }

protected:

    QColor      m_Color;
    QBrush      m_Brush;
};


#endif // _HIGHLIGHTBRUSH_HPP_
