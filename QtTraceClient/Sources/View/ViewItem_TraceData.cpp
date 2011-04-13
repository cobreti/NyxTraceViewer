#include "ViewItem_TraceData.hpp"


/**
 *
 */
CViewItem_TraceData::CViewItem_TraceData(Nyx::CMemoryPool* pMemPool, const TraceClientCore::CTraceData* pTraceData ) :
BaseType(pMemPool),
m_pTraceData(pTraceData)
{
}


/**
 *
 */
CViewItem_TraceData::~CViewItem_TraceData()
{
}


/**
 *
 */
void CViewItem_TraceData::dbgOutputInfo()
{
    const TraceClientCore::CTraceData*     pTraceData = m_pTraceData;

//    if ( m_pDocTraceData != NULL )
//        pTraceData = m_pDocTraceData->TraceData();

    if ( pTraceData )
        Nyx::CTraceStream(0x0)
            << Nyx::CTF_Text(L"CViewItem_TraceData - ")
            << Nyx::CTF_Text(L"TickCount : ") << Nyx::CTF_Text(pTraceData->TickCount().c_str())
            << Nyx::CTF_Text(L" - ThreadId : ") << Nyx::CTF_Text(pTraceData->ThreadId().c_str())
            << Nyx::CTF_Text(L" - Data : ") << Nyx::CTF_Text(pTraceData->Data().c_str());
    else
        Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"CViewItem_TraceData - ");
}

