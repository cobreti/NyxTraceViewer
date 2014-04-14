#include "ViewTraceMetrics.h"
#include "ViewTracePortal.h"
#include "ViewTracesDisplayCache.h"

#include <QFontMetricsF>
#include <algorithm>


CViewTraceMetrics::CViewTraceMetrics()
{

}



CViewTraceMetrics::~CViewTraceMetrics()
{

}


void CViewTraceMetrics::CalcTraceSize(const CViewTracePortal& tracePortal, const ColumnsIdVector& columnsIds, CViewTracesDisplayCache& displayCache)
{
    auto    fct = [&] (EViewColumnId id)
            {
                this->CalcColumnSize(id, tracePortal, displayCache);
            };


    std::for_each( columnsIds.begin(), columnsIds.end(), fct );
}


void CViewTraceMetrics::CalcColumnSize(EViewColumnId columnId, const CViewTracePortal& tracePortal, CViewTracesDisplayCache& displayCache)
{
    CViewTracesDisplayCache::CEntryId       entryId(tracePortal.traceData()->identifier(), columnId);

    if ( displayCache.hasEntry(entryId) )
        return;

    QFontMetricsF                           metrics(m_Font);
    QString                                 text = tracePortal.GetColumnText(columnId);
    QRectF                                  rcText = metrics.boundingRect(text);

    rcText.adjust(0, 0, 0.5, 0.5);

    m_ColumnsRect[columnId] = rcText;
}


QString CViewTraceMetrics::GetTextInRect( const CViewTracePortal& tracePortal, EViewColumnId columnId, const QRectF& itemArea, const QRectF& rcArea )
{
    QString         text;
    QString         srcText = tracePortal.GetColumnText(columnId);
    QFontMetricsF   metrics(m_Font);
    QRectF          rcText;
    QRectF          adjustedItemArea = itemArea;
    qreal           threshold = metrics.averageCharWidth() / 2;
    QRectF          adjustedArea = rcArea;
    qreal           offset = 0;
    int             startPos = 1;
    int             len = srcText.length();

    adjustedItemArea.adjust( -itemArea.left(), 0, -itemArea.left(), 0 );
    adjustedArea.adjust( -itemArea.left(), 0, -itemArea.left(), 0 );

    rcText = metrics.boundingRect(srcText.mid(0, startPos));

    while ( rcText.right() < adjustedArea.left() && startPos <= len )
    {
        ++ startPos;
        rcText = metrics.boundingRect(srcText.mid(0, startPos));
    }

    startPos --;
    rcText = metrics.boundingRect(srcText.mid(0, startPos));
    offset = rcText.right();

    rcText = metrics.boundingRect(srcText.mid(0, len));
    rcText.adjust(offset, 0, offset, 0);

    while ( rcText.right() - threshold > adjustedArea.right() && len > 0 )
    {
        -- len;
        rcText = metrics.boundingRect(srcText.mid(0, len));
        rcText.adjust(offset, 0, offset, 0);
    }


    text = srcText.mid(startPos, len);

    return text;
}
