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


class CViewTracePainter : public CViewTraceMetrics
{
public:
    CViewTracePainter(QPainter& rPainter);
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

    void Draw( TraceClientCore::CTraceData* pData );

protected:

    void DrawColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId);

    void DrawDataColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId);
    void DrawTickCountColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId);
    void DrawLineNumberColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId);
    void DrawModuleNameColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId);
    void DrawThreadIdColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId);

protected:

    typedef std::map<EViewColumnId, qreal>          TColumnsSizeTable;

protected:

    QPainter&                   m_rPainter;
    QPointF                     m_Origin;
    QSizeF                      m_ViewSize;
    QPointF                     m_Pos;
    float                       m_LineHeight;
    QFont                       m_Font;
    CViewColumnsSettings*       m_pColumnsSettings;
    Nyx::UInt32                 m_LineNumber;
    TColumnsSizeTable           m_ColumnsSize;
    bool                        m_bColumnSizeChanged;
};


#endif // VIEWTRACEPAINTER_H
