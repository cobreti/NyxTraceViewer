#include "TraceData.hpp"


/**
 *
 */
TraceClientCore::CTraceData::CTraceData(Nyx::CMemoryPool* pMemPool) : 
TraceClientCore::CTraceData::BaseType(pMemPool),
m_TimeReference(pMemPool),
m_TickCountReference(pMemPool),
m_ThreadId(pMemPool),
m_TickCount(pMemPool),
m_Data(pMemPool),
m_pOwnerPool(NULL),
m_eType(eTT_User),
m_Flags(),
m_RepositoryId(0),
m_TraceId(0)
{
}


/**
 *
 */
TraceClientCore::CTraceData::~CTraceData()
{
}

