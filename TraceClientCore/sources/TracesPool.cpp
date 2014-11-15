#include "TracesPool.hpp"


/**
 *
 */
TraceClientCore::CTracesPool::CTracesPool(Nyx::CMemoryPool* pMemoryPool, const QString& name) :
	m_pRepository(NULL),
    m_Name(name),
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
void TraceClientCore::CTracesPool::SetName(const QString& name)
{
    m_Name = name;
}


/**
 *
 */
void TraceClientCore::CTracesPool::setDescription(const QString& description)
{
    m_Description = description;
}

