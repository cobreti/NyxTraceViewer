#ifndef VIEWTRACEPAINTER_H
#define VIEWTRACEPAINTER_H

#include <Nyx.hpp>

#include <QPainter>
#include "ViewTraceMetrics.h"
#include "ViewColumnId.hpp"

#include <map>


namespace TraceClientCore
{
    class CTraceData;
}

class CViewColumnsSettings;
class CViewColumnSettings;
class CViewTracesDisplayCache;
class CDynamicHighlightsDirectory;

class CViewTracePainter
{
public:

    class CPaintContext
    {
        friend class CViewTracePainter;

    public:
        CPaintContext();
        CPaintContext(const CPaintContext& context);
        virtual ~CPaintContext();

        const CPaintContext& operator = (const CPaintContext& context);

        CViewTracePortal&       portal() const      { return *m_pPortal; }
        EViewColumnId           columnId() const    { return m_ColumnId; }
        CViewTraceMetrics&      metrics() const     { return *m_pMetrics; }
        const QRectF&           area() const        { return m_Area; }
        QPainter&               qpainter() const    { return *m_pQPainter; }

    protected:

        CViewTracePortal*       m_pPortal;
        EViewColumnId           m_ColumnId;
        CViewTraceMetrics*      m_pMetrics;
        QRectF                  m_Area;
        QPainter*               m_pQPainter;
    };

public:
    CViewTracePainter(QPainter& rPainter, CViewTracesDisplayCache& rDisplayCache);
    virtual ~CViewTracePainter();

    const QPointF&  Origin() const              { return m_Origin; }
    QPointF&        Origin()                    { return m_Origin; }

    const QSizeF&   ViewSize() const            { return m_ViewSize; }
    QSizeF&         ViewSize()                  { return m_ViewSize; }

    const Nyx::UInt32& LineNumber() const       { return m_LineNumber; }
    Nyx::UInt32& LineNumber()                   { return m_LineNumber; }

    const QPointF&  Pos() const                 { return m_Pos; }

    float& LineHeight()                         { return m_LineHeight; }

    CViewColumnsSettings* ColumnsSettings() const       { return m_pColumnsSettings; }
    CViewColumnsSettings*& ColumnsSettings()            { return m_pColumnsSettings; }

    void Init();
    void Release();
    bool columnsWidthChanged() const            { return m_bColumnSizeChanged; }

    bool Done() const;

    void PrepareProcess();
    void Process( TraceClientCore::CTraceData* pData );
    void PrepareDrawing();
    void PreDraw( TraceClientCore::CTraceData* pData, const CDynamicHighlightsDirectory& dynamicHighlights );
//    void PreDraw( TraceClientCore::CTraceData* pData, const CViewTraceObjectsDirectory& directory );
    void Draw( TraceClientCore::CTraceData* pData );

protected:

    void ProcessColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId );
    void DrawColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId);
    bool DisplayColumnData( TraceClientCore::CTraceData* pData, EViewColumnId columnId );

protected:

    typedef std::map<EViewColumnId, qreal>          TColumnsSizeTable;

protected:

    QPainter&                   m_rPainter;
    CViewTracesDisplayCache&    m_rDisplayCache;

    QPointF                     m_Origin;
    QSizeF                      m_ViewSize;
    QPointF                     m_Pos;
    float                       m_LineHeight;
    QFont                       m_Font;
    CViewColumnsSettings*       m_pColumnsSettings;
    Nyx::UInt32                 m_LineNumber;
    TColumnsSizeTable           m_ColumnsSize;
    bool                        m_bColumnSizeChanged;
    CViewTraceMetrics           m_Metrics;

    int                         m_TextMargin;
};


#endif // VIEWTRACEPAINTER_H
