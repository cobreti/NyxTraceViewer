#include "ViewItemThreadIdPainter.hpp"
#include "ViewItem_TraceData.hpp"
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
    const CViewItem_TraceData&      rDataItem = static_cast<const CViewItem_TraceData&>(item);
    QString                         text = QString().fromWCharArray(rDataItem.TraceData()->ThreadId().c_str());

    CViewItemTextPainter::EvaluateSize(settings, item, text);
}


/**
 *
 */
void CViewItemThreadIdPainter::Display(const CViewSettings &settings, CDrawViewItemState &drawstate, CViewItem &item)
{
    const CViewItem_TraceData&      rDataItem = static_cast<const CViewItem_TraceData&>(item);

    if ( rDataItem.TraceData()->Type() == TraceClientCore::CTraceData::eTT_User )
    {
        if ( item.GetOwner() == &item )
        {
            QString                         text = QString().fromWCharArray(rDataItem.TraceData()->ThreadId().c_str());

            CViewItemTextPainter::Display(settings, drawstate, item, text);
        }
        else
        {
            const CViewColumnSettings&      rColSettings = settings.ColumnsSettings()[eVCI_ThreadId];
            drawstate.TextPos().rx() += rColSettings.GetWidth();
        }
    }
    else
    {
        const CViewColumnSettings&      rColSettings = settings.ColumnsSettings()[eVCI_ThreadId];
        QPainter&                       rPainter = drawstate.Painter();

        rPainter.drawLine(  drawstate.TextPos().x() + rColSettings.Margins().left(), 
                            drawstate.TextPos().y() + item.GetSize().height() / 2,
                            drawstate.TextPos().x() + rColSettings.GetWidth() - rColSettings.Margins().width(),
                            drawstate.TextPos().y() + item.GetSize().height() / 2 );

        drawstate.TextPos().rx() += rColSettings.GetWidth();
    }
}


