#include "ViewTraceData.hpp"


/**
 *
 */
CViewTraceData::CViewTraceData(Nyx::CMemoryPool* pMemPool) :
BaseType(pMemPool),
m_bMarked(false)
{
}


/**
 *
 */
CViewTraceData::CViewTraceData(Nyx::CMemoryPool* pMemPool, const CDocTraceData *pDocTraceData, const QSizeF& lineSize) :
BaseType(pMemPool),
m_pDocTraceData(pDocTraceData),
m_Size(lineSize),
m_bMarked(false)
{
}


/**
 *
 */
CViewTraceData::~CViewTraceData()
{
}


