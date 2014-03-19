#include <Nyx.hpp>

#include "ViewTracePainter.h"
#include "TraceData.hpp"
#include "ViewColumnsSettings.hpp"
#include "ViewColumnSettings.hpp"


CViewTracePainter::CViewTracePainter(QPainter &rPainter) :
    m_rPainter(rPainter),
    m_pColumnsSettings(NULL),
    m_LineNumber(0)
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

    const CViewColumnsOrder& colsOrder = m_pColumnsSettings->Order();
    size_t ColumnsCount = colsOrder.Count();
    size_t ColumnIndex = 0;
    EViewColumnId ColumnId;

    while (ColumnIndex < ColumnsCount)
    {
        ColumnId = colsOrder[ColumnIndex];
        CViewColumnSettings& ColumnSettings = (*m_pColumnsSettings)[ColumnId];

        ColumnSettings.SetWidth(100.0f);

        DrawColumn(pData, ColumnSettings, ColumnId);

        ++ ColumnIndex;
    }


//    QFontMetricsF           metrics(m_Font);
//    QRectF                  rcText;
//    QString                 text = QString::fromWCharArray(pData->Data().c_str());
//    QRectF                  rcArea;

//    rcArea = QRectF(m_Pos.x(), m_Pos.y(), m_ViewSize.width()-m_Pos.x(), m_ViewSize.height() - m_Pos.y());

//    rcText = metrics.boundingRect(text);

//    m_rPainter.setFont(m_Font);
//    m_rPainter.drawText(rcArea, Qt::AlignLeft, text);

    m_Pos.ry() += m_LineHeight;
}


void CViewTracePainter::DrawColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId)
{
    switch (columnId)
    {
        case eVCI_LineNumber:
            DrawLineNumberColumn(pData, settings, columnId);
            break;
        case eVCI_Data:
            DrawDataColumn(pData, settings, columnId);
            break;
    }

    m_Pos.rx() += settings.GetWidth();
}


void CViewTracePainter::DrawDataColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId)
{
    QFontMetricsF           metrics(m_Font);
    QRectF                  rcText;
    QString                 text = QString::fromWCharArray(pData->Data().c_str());
    QRectF                  rcArea;

    rcArea = QRectF(m_Pos.x(), m_Pos.y(), m_ViewSize.width()-m_Pos.x(), m_ViewSize.height() - m_Pos.y());

    rcText = metrics.boundingRect(text);

    m_rPainter.setFont(m_Font);
    m_rPainter.drawText(rcArea, Qt::AlignLeft, text);
}


void CViewTracePainter::DrawLineNumberColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId)
{
    QFontMetricsF           metrics(m_Font);
    QRectF                  rcText;
    QString                 text = QString::number(m_LineNumber);
    QRectF                  rcArea;

    rcArea = QRectF(    m_Pos.x() + settings.Margins().left(),
                        m_Pos.y() + settings.Margins().top(),
                        m_ViewSize.width() - m_Pos.x() - settings.Margins().width(),
                        m_ViewSize.height() - m_Pos.y() - settings.Margins().height() );

    rcText = metrics.boundingRect(text);

    m_rPainter.setFont(m_Font);
    m_rPainter.drawText(rcArea, Qt::AlignLeft, text);
}
