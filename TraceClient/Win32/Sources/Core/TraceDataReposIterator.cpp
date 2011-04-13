#include "TraceDataReposIterator.hpp"
#include "TraceDataRepos.hpp"

/**
 *
 */
CTraceDataReposIterator::CTraceDataReposIterator( const CTraceDataRepos& rRepos ) :
m_rRepos(rRepos),
m_Index(0)
{
	m_Pos = m_rRepos.m_TracesData.end();
}


/**
 *
 */
CTraceDataReposIterator::~CTraceDataReposIterator()
{
}


/**
 *
 */
bool CTraceDataReposIterator::MTLock()
{
	return const_cast<CTraceDataRepos&>(m_rRepos).MTLock(Nyx::eMTAM_Read );
}


/**
 *
 */
bool CTraceDataReposIterator::MTTryLock()
{
	return const_cast<CTraceDataRepos&>(m_rRepos).MTTryLock(Nyx::eMTAM_Read);
}


/**
 *
 */
void CTraceDataReposIterator::MTUnlock()
{
	const_cast<CTraceDataRepos&>(m_rRepos).MTUnlock( Nyx::eMTAM_Read );
}


/**
 *
 */
const CTraceDataReposIterator& CTraceDataReposIterator::operator = ( const CTraceDataReposIterator& pos )
{
	if ( &m_rRepos == &pos.m_rRepos )
	{
		m_Pos = pos.m_Pos;
		m_Index = pos.m_Index;
	}

	return *this;
}


/**
 *
 */
CTraceDataReposIterator& CTraceDataReposIterator::operator ++ ()
{
	++ m_Pos;
	++ m_Index;

	return *this;
}


/**
 *
 */
CTraceDataReposIterator& CTraceDataReposIterator::operator -- ()
{
	-- m_Pos;
	-- m_Index;

	return *this;
}
