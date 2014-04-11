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


class CViewTraceMetrics
{
public:
    CViewTraceMetrics();
    virtual ~CViewTraceMetrics();

public:

    void CalcTraceSize( TraceClientCore::CTraceData* pData, const ColumnsIdVector& columnsIds );

protected:

    void CalcColumnSize(EViewColumnId columnId, const QString& text);

protected:

    typedef     std::map<EViewColumnId, QRectF>     TColumnsRect;

protected:

    TColumnsRect            m_ColumnsRect;
    QFont                   m_Font;
};



#endif // VIEWTRACEMETRICS_H
