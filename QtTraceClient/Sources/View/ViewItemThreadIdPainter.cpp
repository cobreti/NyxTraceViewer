#include "ViewItemThreadIdPainter.hpp"
#include "ViewItem.hpp"
#include "ViewSettings.hpp"
#include "ViewColumnsSettings.hpp"
#include "ViewColumnSettings.hpp"


CViewItemPainterRef     CViewItemThreadIdPainter::s_refPainter;

/**
 *
 */
CViewItemPainter* CViewItemThreadIdPainter::Instance()
{
    if ( !s_refPainter.Valid() )
        s_refPainter = new CViewItemThreadIdPainter();

    return s_refPainter;
}


/**
 *
 */
CViewItemThreadIdPainter::CViewItemThreadIdPainter()
{
}


/**
 *
 */
CViewItemThreadIdPainter::~CViewItemThreadIdPainter()
{
}


/**
 *
 */
void CViewItemThreadIdPainter::EvaluateSize(CViewSettings &settings, CViewItem &item)
{
    CViewItemTextPainter::EvaluateSize(settings, item, item.GetItemString(CViewItem::eII_ThreadId) );
}


/**
 *
 */
void CViewItemThreadIdPainter::Display(const CViewSettings &settings, CDrawViewItemState &drawstate, CViewItem &item)
{
    QString     text = item.GetItemString( CViewItem::eII_ThreadId );

    if ( text.isEmpty() )
    {
        const CViewColumnSettings&      rColSettings = settings.ColumnsSettings()[eVCI_ThreadId];
        QPainter&                       rPainter = drawstate.Painter();

        rPainter.drawLine(  drawstate.TextPos().x() + rColSettings.Margins().left(), 
                            drawstate.TextPos().y() + item.GetSize().height() / 2,
                            drawstate.TextPos().x() + rColSettings.GetWidth() - rColSettings.Margins().width(),
                            drawstate.TextPos().y() + item.GetSize().height() / 2 );

        drawstate.TextPos().rx() += rColSettings.GetWidth();
    }
    else if ( item.GetOwner() == &item )
    {
        CViewItemTextPainter::Display(settings, drawstate, item, text);
    }
    else
    {
        const CViewColumnSettings&      rColSettings = settings.ColumnsSettings()[eVCI_ThreadId];
        drawstate.TextPos().rx() += rColSettings.GetWidth();
    }
}


