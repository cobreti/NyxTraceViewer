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
