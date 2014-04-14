#include <Nyx.hpp>

#include "ViewTracePainter.h"
#include "TraceData.hpp"
#include "ViewColumnsSettings.hpp"
#include "ViewColumnSettings.hpp"
#include "TracesPool.hpp"
#include "ViewTracePortal.h"
#include "View/ViewTracesDisplayCache.h"


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

    m_Pos = QPointF(0, m_Origin.y());
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

    CViewTracesDisplayCache::CEntryId       entryId(TracePortal.traceData()->identifier(), columnId);
    CViewTracesDisplayCache::CEntryData     entryData;
    QRectF                                  rcArea;

    if ( m_rDisplayCache.hasEntry(entryId) )
    {
        entryData = m_rDisplayCache[entryId];

        rcArea = entryData.itemArea();
        rcArea.adjust(m_Origin.x(), 0, m_Origin.x(), 0);

        if ( DisplayColumnData(pData, columnId) )
        {
            m_rPainter.drawText(rcArea, Qt::AlignLeft, TracePortal.GetColumnText(columnId));
        }

        m_Pos.rx() += entryData.columnWidth() + settings.Margins().width();
    }
    else
    {
        qreal                   colWidth = m_ColumnsSize[columnId];

        rcArea = m_Metrics.ColumnRect(columnId);

        if (settings.AutoWidth())
        {
            colWidth = std::max(colWidth, rcArea.width());
            m_ColumnsSize[columnId] = colWidth;
        }

        colWidth = settings.GetWidth();
        rcArea.moveTo(m_Pos.x() + settings.Margins().left(), m_Pos.y() + settings.Margins().top());

        entryData.itemArea() = rcArea;
        entryData.margins() = settings.Margins();
        entryData.traceData() = pData;
        entryData.columnWidth() = colWidth;
        entryData.lineNumber() = m_LineNumber;
        m_rDisplayCache.setEntry(entryId, entryData);

        rcArea.adjust(m_Origin.x(), 0, m_Origin.x(), 0);

        if ( DisplayColumnData(pData, columnId) )
        {
            m_rPainter.drawText(rcArea, Qt::AlignLeft, TracePortal.GetColumnText(columnId));
        }


        m_Pos.rx() += colWidth + settings.Margins().width();
    }
}


bool CViewTracePainter::DisplayColumnData( TraceClientCore::CTraceData* pData, EViewColumnId columnId )
{
    if (    pData->Level() > 0 &&
            (eVCI_ModuleName == columnId || eVCI_ThreadId == columnId || eVCI_TickCount == columnId) )
    {
        return false;
    }

    return true;
}
