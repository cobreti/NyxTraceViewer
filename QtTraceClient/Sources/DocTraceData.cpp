#include "DocTraceData.hpp"


/**
 *
 */
CDocTraceData::CDocTraceData(Nyx::CMemoryPool* pMemPool) :
BaseType(pMemPool)
{
}


/**
 *
 */
CDocTraceData::CDocTraceData(Nyx::CMemoryPool* pMemPool, const TraceClientCore::CTraceData* pData) :
BaseType(pMemPool),
m_pTraceData(pData)
{
}


/**
 *
 */
CDocTraceData::~CDocTraceData()
{
}

