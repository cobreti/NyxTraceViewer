#include "UITraceDataRepositoryIterator.hpp"


/**
 *
 */
CUITraceDataRepositoryIterator::CUITraceDataRepositoryIterator( const CUITraceDataRepository& rRepos ) :
m_rRepos(rRepos),
m_Index(-1)
{
}


/**
 *
 */
CUITraceDataRepositoryIterator::~CUITraceDataRepositoryIterator()
{
}


/**
 *
 */
const CUITraceDataRepositoryIterator& CUITraceDataRepositoryIterator::operator = ( const CUITraceDataRepositoryIterator& pos )
{
	if ( &m_rRepos != &pos.m_rRepos )
		return *this;

	m_Pos = pos.m_Pos;
	m_Index = pos.m_Index;
	return *this;
}


/**
 *
 */
bool CUITraceDataRepositoryIterator::operator == ( const CUITraceDataRepositoryIterator& pos ) const
{
	return (m_Pos == pos.m_Pos);
}


/**
 *
 */
bool CUITraceDataRepositoryIterator::operator != ( const CUITraceDataRepositoryIterator& pos ) const
{
	return (m_Pos != pos.m_Pos);
}


/**
 *
 */
size_t CUITraceDataRepositoryIterator::Index() const
{
	return m_Index;
}


/**
 *
 */
bool CUITraceDataRepositoryIterator::MTLock()
{
	return const_cast<CUITraceDataRepository&>(m_rRepos).MTLock( Nyx::eMTAM_Read );
}


/**
 *
 */
bool CUITraceDataRepositoryIterator::MTTryLock()
{
	return const_cast<CUITraceDataRepository&>(m_rRepos).MTTryLock( Nyx::eMTAM_Read );
}


/**
 *
 */
void CUITraceDataRepositoryIterator::MTUnlock()
{
	const_cast<CUITraceDataRepository&>(m_rRepos).MTUnlock( Nyx::eMTAM_Read );
}


/**
 *
 */
void CUITraceDataRepositoryIterator::Goto( size_t new_pos )
{
	if ( m_Index == -1 )
		return;

	while ( m_Index > new_pos )
	{
		-- m_Pos;
		-- m_Index;
	}

	while ( m_Index < new_pos )
	{
		++ m_Pos;
		++ m_Index;
	}
}


/**
 *
 */
CUITraceDataRepositoryIterator& CUITraceDataRepositoryIterator::operator ++ ()
{
	++ m_Pos;
	++ m_Index;
	return *this;
}


/**
 *
 */
CUITraceDataRepositoryIterator& CUITraceDataRepositoryIterator::operator -- ()
{
	-- m_Pos;
	-- m_Index;
	return *this;
}


