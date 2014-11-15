#include "ViewTracePortal.h"
#include "TraceData.hpp"
#include "TracesPool.hpp"
#include "TraceChannel.hpp"

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
        text = m_rTraceData.Data();
        break;
    case eVCI_TickCount:
        text = m_rTraceData.TickCount();
        break;
    case eVCI_ModuleName:
        text = m_rTraceData.Channel()->Name();
//        text = "Default"; //m_rTraceData.OwnerPool();
        break;
    case eVCI_ThreadId:
        text = m_rTraceData.ThreadId();
        break;
    }

    return text;
}

