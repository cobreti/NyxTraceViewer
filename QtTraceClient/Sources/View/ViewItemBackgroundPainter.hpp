#ifndef VIEWITEMBACKGROUNDPAINTER_HPP
#define VIEWITEMBACKGROUNDPAINTER_HPP

#include "ViewItemRowPainter.hpp"

/**
 *
 */
class CViewItemBackgroundPainter : public CViewItemRowPainter
{
public:

    static CViewItemPainter* Instance();

public:
    CViewItemBackgroundPainter();
    virtual ~CViewItemBackgroundPainter();

    virtual void Display( const CViewSettings& settings, CDrawViewItemState& drawstate, CViewItem& item );
    void SetBkgndColor( const QColor& color );

protected:

    QImage*     m_pBkgndImage;

private:

    static CViewItemPainterRef     s_refPainter;
};

#endif // VIEWITEMBACKGROUNDPAINTER_HPP
