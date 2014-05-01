#include "ViewTracePortal.h"
#include "TraceData.hpp"
#include "TracesPool.hpp"


CViewTracePortal::CViewTracePortal(TraceClientCore::CTraceData &rTraceData, Nyx::UInt32 lineNumber) :
    m_rTraceData(rTraceData),
    m_LineNumber(lineNumber)
{

}



CViewTracePortal::~CViewTracePortal()
{

}


QString CViewTracePortal::GetColumnText(EViewColumnId columnId) const
{
    QString     text;

    switch (columnId)
    {
    case eVCI_LineNumber:
        text = QString::number(m_LineNumber+1);
        break;
    case eVCI_Data:
        text = QString::fromWCharArray(m_rTraceData.Data().c_str());
        break;
    case eVCI_TickCount:
        text = QString::fromWCharArray(m_rTraceData.TickCount().c_str());
        break;
    case eVCI_ModuleName:
        text = QString::fromWCharArray(m_rTraceData.OwnerPool()->Name().c_str());
        break;
    case eVCI_ThreadId:
        text = QString::fromWCharArray(m_rTraceData.ThreadId().c_str());
        break;
    }

    return text;
}

