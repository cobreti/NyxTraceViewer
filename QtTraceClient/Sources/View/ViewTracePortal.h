#ifndef VIEWTRACEPORTAL_H
#define VIEWTRACEPORTAL_H

#include "ViewColumnId.hpp"

#include <Nyx.hpp>
#include <QString>


namespace TraceClientCore
{
    class CTraceData;
}



class CViewTracePortal
{
public:
    CViewTracePortal(TraceClientCore::CTraceData& rTraceData, Nyx::UInt32 lineNumber = 0);
    ~CViewTracePortal();

    QString GetColumnText(EViewColumnId columnId) const;

    TraceClientCore::CTraceData*        traceData() const       { return &m_rTraceData; }
    Nyx::UInt32                         lineNumber() const      { return m_LineNumber; }

protected:

    TraceClientCore::CTraceData&        m_rTraceData;
    Nyx::UInt32                         m_LineNumber;
};


#endif // VIEWTRACEPORTAL_H
