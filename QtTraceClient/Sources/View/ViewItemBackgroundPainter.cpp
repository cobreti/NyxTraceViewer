#include "ViewItemBackgroundPainter.hpp"
#include "ViewItem.hpp"


CViewItemPainterRef     CViewItemBackgroundPainter::s_refPainter;


/**
 *
 */
CViewItemPainter* CViewItemBackgroundPainter::Instance()
{
    if ( !s_refPainter.Valid() )
        s_refPainter = new CViewItemBackgroundPainter();

    return s_refPainter;
}


/**
 *
 */
CViewItemBackgroundPainter::CViewItemBackgroundPainter() :
CViewItemRowPainter()
{
    m_pBkgndImage = new QImage(":/View/Images/VGradientInner.png");
    SetBkgndColor(QColor(141, 254, 251));
}


/**
 *
 */
CViewItemBackgroundPainter::~CViewItemBackgroundPainter()
{
}


/**
 *
 */
void CViewItemBackgroundPainter::Display(const CViewSettings&, CDrawViewItemState &drawstate, CViewItem &item)
{
    QPainter&       rPainter = drawstate.Painter();

    if ( item.HasFlag(CViewItem::eVIF_Marked) )
    {
        QRectF      rcBkgnd( drawstate.TextPos().x(), drawstate.TextPos().y(),
                                drawstate.ViewRect().width(),
                                item.GetSize().height() );

        rPainter.drawImage( rcBkgnd, *m_pBkgndImage );
    }
}


/**
 *
 */
void CViewItemBackgroundPainter::SetBkgndColor( const QColor& color )
{
    if ( !m_pBkgndImage )
        return;

    int     ImageHeight = m_pBkgndImage->size().height();
    int     ImageWidth = m_pBkgndImage->size().width();
    int     x, y;

    for (y = 0; y < ImageHeight; ++y)
    {
        QColor      pixelColor = m_pBkgndImage->pixel(0, y);
        float       ratio = pixelColor.red() / 255.0;
        QColor      finalColor( color.red()*ratio, color.green()*ratio, color.blue()*ratio );

        for (x = 0; x < ImageWidth; ++x)
            m_pBkgndImage->setPixel(x, y, finalColor.rgb());
    }
}
