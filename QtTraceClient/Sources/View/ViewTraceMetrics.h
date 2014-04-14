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
    CViewTraceMetrics();
    virtual ~CViewTraceMetrics();

public:

    void CalcTraceSize( const CViewTracePortal& tracePortal, const ColumnsIdVector& columnsIds, CViewTracesDisplayCache& displayCache );
    const QRectF& ColumnRect( const EViewColumnId id )                  { return m_ColumnsRect[id]; }
    QString GetTextInRect( const CViewTracePortal& tracePortal, EViewColumnId columnId, const QRectF& itemArea, const QRectF& rcArea );

protected:

    void CalcColumnSize(EViewColumnId columnId, const CViewTracePortal& tracePortal, CViewTracesDisplayCache& displayCache);

protected:

    typedef     std::map<EViewColumnId, QRectF>     TColumnsRect;

protected:

    TColumnsRect            m_ColumnsRect;
    QFont                   m_Font;
};



#endif // VIEWTRACEMETRICS_H
