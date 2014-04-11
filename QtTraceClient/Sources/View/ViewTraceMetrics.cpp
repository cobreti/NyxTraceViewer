#include "ViewTraceMetrics.h"
#include "ViewTracePortal.h"

#include <QFontMetricsF>
#include <algorithm>


CViewTraceMetrics::CViewTraceMetrics()
{

}



CViewTraceMetrics::~CViewTraceMetrics()
{

}


void CViewTraceMetrics::CalcTraceSize(TraceClientCore::CTraceData *pData, const ColumnsIdVector& columnsIds)
{
    CViewTracePortal        TracePortal(*pData);
    auto                    fct = [&] (EViewColumnId id)
                                    {
                                        this->CalcColumnSize(id, TracePortal.GetColumnText(id));
                                    };


    std::for_each( columnsIds.begin(), columnsIds.end(), fct );
}


void CViewTraceMetrics::CalcColumnSize(EViewColumnId columnId, const QString& text)
{
    QFontMetricsF           metrics(m_Font);
    QRectF                  rcText = metrics.boundingRect(text);

    m_ColumnsRect[columnId] = rcText;
}
