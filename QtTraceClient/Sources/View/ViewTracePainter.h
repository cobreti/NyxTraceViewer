#ifndef VIEWTRACEPAINTER_H
#define VIEWTRACEPAINTER_H

#include <QPainter>
#include "ViewColumnId.hpp"


namespace TraceClientCore
{
    class CTraceData;
}

class CViewColumnsSettings;
class CViewColumnSettings;


class CViewTracePainter
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
    bool Done() const;

    void Draw( TraceClientCore::CTraceData* pData );

protected:

    void DrawColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId);

    void DrawDataColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId);
    void DrawLineNumberColumn( TraceClientCore::CTraceData* pData, CViewColumnSettings& settings, EViewColumnId columnId);

protected:

    QPainter&                   m_rPainter;
    QPointF                     m_Origin;
    QSizeF                      m_ViewSize;
    QPointF                     m_Pos;
    float                       m_LineHeight;
    QFont                       m_Font;
    CViewColumnsSettings*       m_pColumnsSettings;
    Nyx::UInt32                 m_LineNumber;
};


#endif // VIEWTRACEPAINTER_H
