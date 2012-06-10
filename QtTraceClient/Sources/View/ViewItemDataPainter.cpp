#include "ViewItemDataPainter.hpp"
#include "ViewItem_TraceData.hpp"
#include "ViewItemSettings.hpp"
#include "ViewSettings.hpp"


CViewItemPainterRef     CViewItemDataPainter::s_refPainter;


/**
 *
 */
CViewItemPainter* CViewItemDataPainter::Instance()
{
    if ( !s_refPainter.Valid() )
        s_refPainter = new CViewItemDataPainter();

    return s_refPainter;
}


/**
 *
 */
CViewItemDataPainter::CViewItemDataPainter() :
CViewItemTextPainter()
{
}


/**
 *
 */
CViewItemDataPainter::~CViewItemDataPainter()
{
}


/**
 *
 */
void CViewItemDataPainter::EvaluateSize(CViewSettings &settings, CViewItem &item)
{
    CViewItem_TraceData&        rItemData = static_cast<CViewItem_TraceData&>(item);
    QString                     text = QString().fromWCharArray(rItemData.TraceData()->Data().c_str());
    const Nyx::CRange&          range = rItemData.TextRange();

    CViewItemTextPainter::EvaluateSize(settings, item, text.mid(range.Start(), range.Length()));
}


/**
 *
 */
void CViewItemDataPainter::Display( const CViewSettings &settings,
                                            CDrawViewItemState &drawstate,
                                            CViewItem &item )
{
    const CViewColumnSettings&      rColSettings = settings.ColumnsSettings()[ CViewItemPainter::PainterId2ColumnId(Id()) ];
    CViewItem_TraceData&            rItemData = static_cast<CViewItem_TraceData&>(item);
    QString                         full_text = QString().fromWCharArray(rItemData.TraceData()->Data().c_str());
    const Nyx::CRange&              range = rItemData.TextRange();
    QString                         text = full_text.mid(range.Start(), range.Length());
    QFontMetricsF                   Metrics(Font());

    drawstate.Highlighter()->OnPreItemDisplay(settings, rColSettings, drawstate, Metrics, text);

    CViewItemTextPainter::Display(settings, drawstate, item, text);

    drawstate.Highlighter()->OnPostItemDisplay(settings, rColSettings, drawstate, Metrics, text);
}


