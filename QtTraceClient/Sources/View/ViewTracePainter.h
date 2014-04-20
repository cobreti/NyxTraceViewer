#ifndef VIEWTRACEPAINTER_H
#define VIEWTRACEPAINTER_H

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
class CViewTraceObjectsDirectory;


class CViewTracePainter
{
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
    void PreDraw( TraceClientCore::CTraceData* pData, const CViewTraceObjectsDirectory& directory );
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
};


#endif // VIEWTRACEPAINTER_H