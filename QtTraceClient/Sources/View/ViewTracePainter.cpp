#include <Nyx.hpp>

#include "ViewTracePainter.h"
#include "TraceData.hpp"


CViewTracePainter::CViewTracePainter(QPainter &rPainter) :
    m_rPainter(rPainter)
{

}


CViewTracePainter::~CViewTracePainter()
{

}


void CViewTracePainter::Init()
{
    m_Pos = m_Origin;
}


bool CViewTracePainter::Done() const
{
    return m_Pos.y() >= m_ViewSize.height();
}


void CViewTracePainter::Draw( TraceClientCore::CTraceData* pData )
{
    m_Pos.rx() = m_Origin.x();

    QFontMetricsF           metrics(m_Font);
    QRectF                  rcText;
    QString                 text = QString::fromWCharArray(pData->Data().c_str());
    QRectF                  rcArea;

    rcArea = QRectF(m_Pos.x(), m_Pos.y(), m_ViewSize.width()-m_Pos.x(), m_ViewSize.height() - m_Pos.y());

    rcText = metrics.boundingRect(text);

    m_rPainter.setFont(m_Font);
    m_rPainter.drawText(rcArea, Qt::AlignLeft, text);

    m_Pos.ry() += m_LineHeight;
}

