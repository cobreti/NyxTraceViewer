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
    QColor      color = Qt::GlobalColor::yellow;

    QBrush      brush(color);
    QBrush      oldBrush = rPainter.brush();
    QPen        oldPen = rPainter.pen();
    QRectF      rcHilight = m_rcHilight;

    rcHilight.adjust(itemRect.left(), 0, itemRect.left(), 0);
    rcHilight.setTop(itemRect.top());
    rcHilight.setBottom(itemRect.bottom());

    rPainter.setPen(Qt::GlobalColor::darkYellow);
    rPainter.setBrush(brush);
    rPainter.drawRoundedRect(rcHilight, 2, 2);

    rPainter.setPen(oldPen);
    rPainter.setBrush(oldBrush);
//    rPainter.fillRect(rcHilight, brush);
}
