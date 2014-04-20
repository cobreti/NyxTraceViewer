#include "ViewTraceSectionHilight.h"

#include <QPainter>
#include <QColor>
#include <QBrush>

CViewTraceSectionHilight::CViewTraceSectionHilight(TraceClientCore::CTraceData& rTraceData, const EViewColumnId& columnId, const QRectF& rcHilight) :
    CViewTraceObject(rTraceData),
    m_ColumnId(columnId),
    m_rcHilight(rcHilight)
{
}


CViewTraceSectionHilight::~CViewTraceSectionHilight()
{
}


void CViewTraceSectionHilight::Draw(QPainter &rPainter, const QRectF &itemRect)
{
    QBrush      brush(Qt::GlobalColor::yellow);
    QRectF      rcHilight = m_rcHilight;

    rcHilight.adjust(itemRect.left(), 0, itemRect.left(), 0);
    rcHilight.setTop(itemRect.top());
    rcHilight.setBottom(itemRect.bottom());

    rPainter.fillRect(rcHilight, brush);
}
