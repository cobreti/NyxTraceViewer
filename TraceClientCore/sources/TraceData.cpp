#include "TraceData.hpp"


/**
 *
 */
TraceClientCore::CTraceData::CTraceData(Nyx::CMemoryPool* pMemPool) : 
TraceClientCore::CTraceData::BaseType(pMemPool),
m_ThreadId(pMemPool),
m_TickCount(pMemPool),
m_Data(pMemPool),
m_pOwnerPool(NULL),
m_eType(eTT_User)
{
}


/**
 *
 */
TraceClientCore::CTraceData::~CTraceData()
{
}


/**
 *
 */
//const TraceClientCore::CTraceData& TraceClientCore::CTraceData::operator = (const TraceClientCore::CTraceData& tracedata)
//{
//	if ( this != &tracedata )
//	{
//		m_Data = tracedata.m_Data;
//		m_ThreadId = tracedata.m_ThreadId;
//		m_TickCount = tracedata.m_TickCount;
//		m_pOwnerPool = tracedata.m_pOwnerPool;
//        m_eType = tracedata.m_eType;
//	}
//
//	return *this;
//}
