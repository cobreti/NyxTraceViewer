#ifndef VIEWTRACEMETRICS_H
#define VIEWTRACEMETRICS_H

#include "ViewColumnId.hpp"

#include <QString>
#include <QRectF>
#include <QFont>

#include <map>

namespace TraceClientCore
{
    class CTraceData;
}

class CViewTracePortal;
class CViewTracesDisplayCache;


class CViewTraceMetrics
{
public:

    class CSubSection
    {
    public:
        CSubSection();
        CSubSection(const CSubSection& section);
        ~CSubSection();

        const CSubSection& operator = (const CSubSection& section);

        const QString&                      text() const            { return m_Text; }
        QString&                            text()                  { return m_Text; }

        const int&                          startIndex() const      { return m_StartIndex; }
        int&                                startIndex()            { return m_StartIndex; }

        const int&                          length() const          { return m_Length; }
        int&                                length()                { return m_Length; }

        const QRectF&                       subRect() const         { return m_SubRect; }
        QRectF&                             subRect()               { return m_SubRect; }

    protected:

        QString     m_Text;
        int         m_StartIndex;
        int         m_Length;
        QRectF      m_SubRect;
    };

public:
    CViewTraceMetrics();
    virtual ~CViewTraceMetrics();

public:

    void CalcTraceSize( const CViewTracePortal& tracePortal, const ColumnsIdVector& columnsIds, CViewTracesDisplayCache& displayCache );
    const QRectF& ColumnRect( const EViewColumnId id )                  { return m_ColumnsRect[id]; }
    const CSubSection GetTextInRect( const CViewTracePortal& tracePortal, EViewColumnId columnId, const QRectF& itemArea, const QRectF& rcArea );
    const CSubSection GetSubTextRect( const CViewTracePortal& tracePortal, EViewColumnId columnId, const QRectF& itemArea, int startIndex, int len );

protected:

    void CalcColumnSize(EViewColumnId columnId, const CViewTracePortal& tracePortal, CViewTracesDisplayCache& displayCache);

protected:

    typedef     std::map<EViewColumnId, QRectF>     TColumnsRect;

protected:

    TColumnsRect            m_ColumnsRect;
    QFont                   m_Font;
};



#endif // VIEWTRACEMETRICS_H
