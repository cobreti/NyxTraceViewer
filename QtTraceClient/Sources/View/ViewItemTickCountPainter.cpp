#include "ViewItemTickCountPainter.hpp"
#include "ViewItemSettings.hpp"
#include "ViewItem_TraceData.hpp"
#include "ViewSettings.hpp"
#include "ViewColumnsSettings.hpp"
#include "ViewColumnSettings.hpp"


CViewItemPainterRef     CViewItemTickCountPainter::s_refPainter;


/**
 *
 */
CViewItemPainter* CViewItemTickCountPainter::Instance()
{
    if ( !s_refPainter.Valid() )
        s_refPainter = new CViewItemTickCountPainter();

    return s_refPainter;
}


/**
 *
 */
CViewItemTickCountPainter::CViewItemTickCountPainter() :
CViewItemTextPainter()
{
}


/**
 *
 */
CViewItemTickCountPainter::~CViewItemTickCountPainter()
{
}


/**
 *
 */
void CViewItemTickCountPainter::EvaluateSize(CViewSettings &settings, CViewItem &item)
{
    CViewItem_TraceData&        rItemData = static_cast<CViewItem_TraceData&>(item);
    QString                     text = QString().fromWCharArray(rItemData.TraceData()->TickCount().c_str());

    CViewItemTextPainter::EvaluateSize(settings, item, text);
}


/**
 *
 */
void CViewItemTickCountPainter::Display(const CViewSettings &settings, CDrawViewItemState &drawstate, CViewItem &item)
{
    CViewItem_TraceData&        rItemData = static_cast<CViewItem_TraceData&>(item);

    if ( rItemData.TraceData()->Type() == TraceClientCore::CTraceData::eTT_User )
    {
        QString                     text = QString().fromWCharArray(rItemData.TraceData()->TickCount().c_str());

        CViewItemTextPainter::Display(settings, drawstate, item, text);
    }
    else
    {
        const CViewColumnSettings&      rColSettings = settings.ColumnsSettings()[eVCI_TickCount];
        QPainter&                       rPainter = drawstate.Painter();

        rPainter.drawLine(  drawstate.TextPos().x() + rColSettings.Margins().left(), 
                            drawstate.TextPos().y() + item.GetSize().height() / 2,
                            drawstate.TextPos().x() + rColSettings.GetWidth() - rColSettings.Margins().width(),
                            drawstate.TextPos().y() + item.GetSize().height() / 2 );

        drawstate.TextPos().rx() += rColSettings.GetWidth();
    }
}

