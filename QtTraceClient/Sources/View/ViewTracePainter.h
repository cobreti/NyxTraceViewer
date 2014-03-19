#ifndef VIEWTRACEPAINTER_H
#define VIEWTRACEPAINTER_H

#include <QPainter>


namespace TraceClientCore
{
    class CTraceData;
}


class CViewTracePainter
{
public:
    CViewTracePainter(QPainter& rPainter);
    virtual ~CViewTracePainter();

    const QPointF&  Origin() const              { return m_Origin; }
    QPointF&        Origin()                    { return m_Origin; }

    const QSizeF&   ViewSize() const            { return m_ViewSize; }
    QSizeF&         ViewSize()                  { return m_ViewSize; }

    const QPointF&  Pos() const                 { return m_Pos; }

    float& LineHeight()                         { return m_LineHeight; }

    void Init();
    bool Done() const;

    void Draw( TraceClientCore::CTraceData* pData );

protected:

    QPainter&       m_rPainter;
    QPointF         m_Origin;
    QSizeF          m_ViewSize;
    QPointF         m_Pos;
    float           m_LineHeight;
    QFont           m_Font;
};


#endif // VIEWTRACEPAINTER_H
