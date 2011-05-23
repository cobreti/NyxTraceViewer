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

