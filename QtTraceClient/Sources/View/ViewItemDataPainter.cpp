#include "ViewItemDataPainter.hpp"
#include "ViewItem.hpp"
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
    CViewItemTextPainter::EvaluateSize(settings, item, item.GetItemString(CViewItem::eII_TraceData));
}


/**
 *
 */
void CViewItemDataPainter::Display( const CViewSettings &settings,
                                    CDrawViewItemState &drawstate,
                                    CViewItem &item )
{
    const CViewColumnSettings&      rColSettings = settings.ColumnsSettings()[ CViewItemPainter::PainterId2ColumnId(Id()) ];
    QString                         text = item.GetItemString( CViewItem::eII_TraceData );
    QFontMetricsF                   Metrics(Font());

    drawstate.Highlighter()->OnPreItemDisplay(settings, rColSettings, drawstate, Metrics, text);

    CViewItemTextPainter::Display(settings, drawstate, item, text);

    drawstate.Highlighter()->OnPostItemDisplay(settings, rColSettings, drawstate, Metrics, text);
}


