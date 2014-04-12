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


void CViewTraceMetrics::CalcTraceSize(const CViewTracePortal& tracePortal, const ColumnsIdVector& columnsIds)
{
    auto                    fct = [&] (EViewColumnId id)
                                    {
                                        this->CalcColumnSize(id, tracePortal.GetColumnText(id));
                                    };


    std::for_each( columnsIds.begin(), columnsIds.end(), fct );
}


void CViewTraceMetrics::CalcColumnSize(EViewColumnId columnId, const QString& text)
{
    QFontMetricsF           metrics(m_Font);
    QRectF                  rcText = metrics.boundingRect(text);

    rcText.adjust(0, 0, 0.5, 0.5);

    m_ColumnsRect[columnId] = rcText;
}
