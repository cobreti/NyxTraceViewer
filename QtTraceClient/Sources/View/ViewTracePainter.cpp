#include <Nyx.hpp>

#include "ViewTracePainter.h"
#include "TraceData.hpp"
#include "ViewColumnsSettings.hpp"
#include "ViewColumnSettings.hpp"
#include "TracesPool.hpp"
#include "ViewTracePortal.h"
#include "View/ViewTracesDisplayCache.h"
#include "Decorations/ViewTraceObject.h"
#include "Decorations/DynamicHighlightsDirectory.h"


CViewTracePainter::CViewTracePainter(QPainter &rPainter, CViewTracesDisplayCache& rDisplayCache) :
    m_rPainter(rPainter),
    m_rDisplayCache(rDisplayCache),
    m_pColumnsSettings(NULL),
    m_LineNumber(0),
    m_bColumnSizeChanged(false),
    m_TextMargin(5)
{
}


CViewTracePainter::~CViewTracePainter()
{

}


void CViewTracePainter::Init()
{
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


void CViewTracePainter::PrepareProcess()
{
    m_Pos = QPointF(0, m_Origin.y());
    m_bColumnSizeChanged = false;
}


void CViewTracePainter::Process( TraceClientCore::CTraceData* pData )
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

        ProcessColumn(pData, ColumnSettings, ColumnId);

        ++ ColumnIndex;
    }

    m_Pos.ry() += m_LineHeight;
}



void CViewTracePainter::PrepareDrawing()
{
    m_Pos = QPointF(0, m_Origin.y());
}


void CViewTracePainter::PreDraw( TraceClientCore::CTraceData* pData, const CDynamicHighlightsDirectory& dynamicHighlights )
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
        CViewColumnSettings&                    ColumnSettings = (*m_pColumnsSettings)[ColumnId];
        CTraceSectionId                         sectionId(TracePortal.traceData()->identifier(), ColumnId);
        CViewTracesDisplayCache::CEntryData     entryData;

        if ( m_rDisplayCache.hasEntry(sectionId) )
        {
            entryData = m_rDisplayCache[sectionId];

            QRectF      rcArea = entryData.itemArea();

            CPaintContext       context;

            context.m_pMetrics = &m_Metrics;
            context.m_pPortal = &TracePortal;
            context.m_Area = rcArea;
            context.m_ColumnId = ColumnId;
            context.m_pQPainter = &m_rPainter;

            dynamicHighlights.Draw(context);

            m_Pos.rx() += entryData.columnWidth() + ColumnSettings.Margins().width();
        }

        ++ ColumnIndex;
    }

    m_Pos.ry() += m_LineHeight;
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


void CViewTracePainter::ProcessColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId)
{
    CViewTracePortal        TracePortal(*pData, m_LineNumber);

    CTraceSectionId                         entryId(TracePortal.traceData()->identifier(), columnId);
    CViewTracesDisplayCache::CEntryData     entryData;
    QRectF                                  rcArea;

    if ( m_rDisplayCache.hasEntry(entryId) )
    {
        entryData = m_rDisplayCache[entryId];

        m_Pos.rx() += entryData.columnWidth() + settings.Margins().width();
    }
    else
    {
        qreal                   colWidth = m_ColumnsSize[columnId];

        rcArea = m_Metrics.ColumnRect(columnId);
        rcArea.setRight( rcArea.right() + m_TextMargin*2 );
        rcArea.setLeft( rcArea.left() + m_TextMargin );

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

        m_Pos.rx() += colWidth + settings.Margins().width();
    }
}


void CViewTracePainter::DrawColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId)
{
    CViewTracePortal        TracePortal(*pData, m_LineNumber);

    CTraceSectionId                         entryId(TracePortal.traceData()->identifier(), columnId);
    CViewTracesDisplayCache::CEntryData     entryData;
    QRectF                                  rcArea;

    if ( !m_rDisplayCache.hasEntry(entryId) )
        return;

    entryData = m_rDisplayCache[entryId];

    rcArea = entryData.itemArea();
//    rcArea.translate( m_TextMargin, 0 );

    if ( columnId != eVCI_LineNumber && pData->Type() == TraceClientCore::CTraceData::eTT_ConnectionStatus_Disconnection )
    {
        qreal   y = rcArea.top() + m_LineHeight / 2;
        QPen oldPen = m_rPainter.pen();
        m_rPainter.setPen( Qt::red );
        m_rPainter.drawLine(rcArea.left(), y-2, rcArea.left() + entryData.columnWidth(), y-2);
        m_rPainter.drawLine(rcArea.left(), y+2, rcArea.left() + entryData.columnWidth(), y+2);
        m_rPainter.setPen(oldPen);
    }
    else if ( DisplayColumnData(pData, columnId) )
    {
        QString     text = TracePortal.GetColumnText(columnId);
        m_rPainter.drawText(rcArea, Qt::AlignLeft, text);
//        m_rPainter.drawRect(rcArea);
    }

    m_Pos.rx() += entryData.columnWidth() + settings.Margins().width();
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



CViewTracePainter::CPaintContext::CPaintContext() :
    m_pPortal(NULL),
    m_ColumnId(eVCI_Count),
    m_pMetrics(NULL),
    m_pQPainter(NULL)
{

}


CViewTracePainter::CPaintContext::CPaintContext(const CPaintContext &context) :
    m_pPortal(context.m_pPortal),
    m_ColumnId(context.m_ColumnId),
    m_pMetrics(context.m_pMetrics),
    m_Area(context.m_Area),
    m_pQPainter(context.m_pQPainter)
{

}


CViewTracePainter::CPaintContext::~CPaintContext()
{

}


const CViewTracePainter::CPaintContext& CViewTracePainter::CPaintContext::operator = (const CPaintContext& context)
{
    m_pPortal = context.m_pPortal;
    m_ColumnId = context.m_ColumnId;
    m_pMetrics = context.m_pMetrics;
    m_Area = context.m_Area;
    m_pQPainter = context.m_pQPainter;

    return *this;
}
