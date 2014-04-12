#include <Nyx.hpp>

#include "ViewTracePainter.h"
#include "TraceData.hpp"
#include "ViewColumnsSettings.hpp"
#include "ViewColumnSettings.hpp"
#include "TracesPool.hpp"
#include "ViewTracePortal.h"


CViewTracePainter::CViewTracePainter(QPainter &rPainter, CViewTracesDisplayCache& rDisplayCache) :
    m_rPainter(rPainter),
    m_rDisplayCache(rDisplayCache),
    m_pColumnsSettings(NULL),
    m_LineNumber(0),
    m_bColumnSizeChanged(false)
{
}


CViewTracePainter::~CViewTracePainter()
{

}


void CViewTracePainter::Init()
{
//    m_ColumnsSize.reserve(eVCI_Count);

    m_Pos = m_Origin;
    m_bColumnSizeChanged = false;

    for (size_t index = 0; index < eVCI_Count; ++index) {
        EViewColumnId id = (EViewColumnId) index;
        m_ColumnsSize[id] = (*m_pColumnsSettings)[id].GetWidth();
    }
}


void CViewTracePainter::Release()
{
    for (size_t index = 0; index < eVCI_Count; ++index) {
        EViewColumnId id = (EViewColumnId) index;

        if ( m_ColumnsSize[id] > (*m_pColumnsSettings)[id].GetWidth() )
        {
            (*m_pColumnsSettings)[id].SetWidth(m_ColumnsSize[id]);
            m_bColumnSizeChanged = true;
        }
    }
}


bool CViewTracePainter::Done() const
{
    return m_Pos.y() >= m_ViewSize.height();
}


void CViewTracePainter::Draw( TraceClientCore::CTraceData* pData )
{
    CViewTracePortal        TracePortal(*pData, m_LineNumber);

    m_Pos.rx() = m_Origin.x();

    const CViewColumnsOrder& colsOrder = m_pColumnsSettings->Order();
    size_t ColumnsCount = colsOrder.Count();
    size_t ColumnIndex = 0;
    EViewColumnId ColumnId;

    m_Metrics.CalcTraceSize(TracePortal, colsOrder.OrderVector(), m_rDisplayCache);

    while (ColumnIndex < ColumnsCount)
    {
        ColumnId = colsOrder[ColumnIndex];
        CViewColumnSettings& ColumnSettings = (*m_pColumnsSettings)[ColumnId];

        DrawColumn(pData, ColumnSettings, ColumnId);

        ++ ColumnIndex;
    }

    m_Pos.ry() += m_LineHeight;
}


void CViewTracePainter::DrawColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId)
{
    CViewTracePortal        TracePortal(*pData, m_LineNumber);
    QRectF                  rcArea = m_Metrics.ColumnRect(columnId);
    qreal                   colWidth = m_ColumnsSize[columnId];

    if (settings.AutoWidth())
    {
        colWidth = std::max(colWidth, rcArea.width());
        m_ColumnsSize[columnId] = colWidth;
    }

    colWidth = settings.GetWidth();
    rcArea.moveTo(m_Pos.x() + settings.Margins().left(), m_Pos.y() + settings.Margins().top());

    m_rPainter.drawText(rcArea, Qt::AlignLeft, TracePortal.GetColumnText(columnId));
//    rcArea.setBottom(m_ViewSize.height() - m_Pos.y());

//    switch (columnId)
//    {
//        case eVCI_LineNumber:
//            DrawLineNumberColumn(pData, settings, columnId);
//            break;
//        case eVCI_Data:
//            DrawDataColumn(pData, settings, columnId);
//            break;
//        case eVCI_TickCount:
//            DrawTickCountColumn(pData, settings, columnId);
//            break;
//        case eVCI_ModuleName:
//            DrawModuleNameColumn(pData, settings, columnId);
//            break;
//        case eVCI_ThreadId:
//            DrawThreadIdColumn(pData, settings, columnId);
//            break;
//    }

//    qreal colWidth = settings.GetWidth() + settings.Margins().width();
    m_Pos.rx() += colWidth + settings.Margins().width();
}


void CViewTracePainter::DrawDataColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId)
{
    QFontMetricsF           metrics(m_Font);
    QRectF                  rcText;
    QString                 text = QString::fromWCharArray(pData->Data().c_str());
    QRectF                  rcArea;
    qreal                   colWidth = m_ColumnsSize[columnId];

    m_rPainter.setFont(m_Font);
    rcText = metrics.boundingRect(text);

    if (settings.AutoWidth())
    {
        colWidth = std::max(colWidth, rcText.width());
        m_ColumnsSize[columnId] = colWidth;
    }

    colWidth = settings.GetWidth();

    rcArea = QRectF(    m_Pos.x() + settings.Margins().left(),
                        m_Pos.y() + settings.Margins().top(),
                        colWidth,
                        m_ViewSize.height() - m_Pos.y());


    m_rPainter.drawText(rcArea, Qt::AlignLeft, text);
}


void CViewTracePainter::DrawTickCountColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId)
{
    if ( pData->Level() > 0 )
        return;

    QFontMetricsF           metrics(m_Font);
    QRectF                  rcText;
    QString                 text = QString::fromWCharArray(pData->TickCount().c_str());
    QRectF                  rcArea;
    qreal                   colWidth = m_ColumnsSize[columnId];

    m_rPainter.setFont(m_Font);
    rcText = metrics.boundingRect(text);

    if (settings.AutoWidth())
    {
        colWidth = std::max(colWidth, rcText.width());
        m_ColumnsSize[columnId] = colWidth;
    }

    colWidth = settings.GetWidth();

    rcArea = QRectF(    m_Pos.x() + settings.Margins().left(),
                        m_Pos.y() + settings.Margins().top(),
                        colWidth,
                        m_ViewSize.height());

    m_rPainter.drawText(rcArea, Qt::AlignLeft, text);
}



void CViewTracePainter::DrawLineNumberColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId)
{
    QFontMetricsF           metrics(m_Font);
    QRectF                  rcText;
    QString                 text = QString::number(m_LineNumber);
    QRectF                  rcArea;
    qreal                   colWidth = m_ColumnsSize[columnId];

    m_rPainter.setFont(m_Font);
    rcText = metrics.boundingRect(text);

    if (settings.AutoWidth())
    {
        colWidth = std::max(colWidth, rcText.width());
        m_ColumnsSize[columnId] = colWidth;
    }

    colWidth = settings.GetWidth();

    rcArea = QRectF(    m_Pos.x() + settings.Margins().left(),
                        m_Pos.y() + settings.Margins().top(),
                        colWidth,
                        m_ViewSize.height() - m_Pos.y() - settings.Margins().height() );


    m_rPainter.drawText(rcArea, Qt::AlignLeft, text);
}


void CViewTracePainter::DrawModuleNameColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId)
{
    if ( pData->Level() > 0 )
        return;

    QFontMetricsF           metrics(m_Font);
    QRectF                  rcText;
    QString                 text = QString::fromWCharArray(pData->OwnerPool()->Name().c_str());
    QRectF                  rcArea;
    qreal                   colWidth = m_ColumnsSize[columnId];

    m_rPainter.setFont(m_Font);
    rcText = metrics.boundingRect(text);

    if (settings.AutoWidth())
    {
        colWidth = std::max(colWidth, rcText.width());
        m_ColumnsSize[columnId] = colWidth;
    }

    colWidth = settings.GetWidth();

    rcArea = QRectF(    m_Pos.x() + settings.Margins().left(),
                        m_Pos.y() + settings.Margins().top(),
                        colWidth,
                        m_ViewSize.height() - m_Pos.y() - settings.Margins().height() );


    m_rPainter.drawText(rcArea, Qt::AlignLeft, text);
}


void CViewTracePainter::DrawThreadIdColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId)
{
    if ( pData->Level() > 0 )
        return;

    QFontMetricsF           metrics(m_Font);
    QRectF                  rcText;
    QString                 text = QString::fromWCharArray(pData->ThreadId().c_str());
    QRectF                  rcArea;
    qreal                   colWidth = m_ColumnsSize[columnId];

    m_rPainter.setFont(m_Font);
    rcText = metrics.boundingRect(text);

    if (settings.AutoWidth())
    {
        colWidth = std::max(colWidth, rcText.width());
        m_ColumnsSize[columnId] = colWidth;
    }

    colWidth = settings.GetWidth();

    rcArea = QRectF(    m_Pos.x() + settings.Margins().left(),
                        m_Pos.y() + settings.Margins().top(),
                        colWidth,
                        m_ViewSize.height() - m_Pos.y() - settings.Margins().height() );


    m_rPainter.drawText(rcArea, Qt::AlignLeft, text);
}
