#include "TracesPool.hpp"


/**
 *
 */
TraceClientCore::CTracesPool::CTracesPool(Nyx::CMemoryPool* pMemoryPool, const wchar_t* wszName) :
	m_pRepository(NULL),
	m_Name(wszName),
	m_refMemoryPool(pMemoryPool)
{
	m_pRepository = new CTraceDataRepository();
}


/**
 *
 */
TraceClientCore::CTracesPool::~CTracesPool()
{
	delete m_pRepository;
}


/**
 *
 */
void TraceClientCore::CTracesPool::SetName(const wchar_t* wszName)
{
	m_Name = wszName;
}


/**
 *
 */
void TraceClientCore::CTracesPool::setDescription(const wchar_t* wszDescription)
{
	m_Description = wszDescription;
}

