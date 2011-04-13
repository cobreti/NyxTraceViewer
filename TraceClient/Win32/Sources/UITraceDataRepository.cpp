#include "UITraceDataRepository.hpp"
#include "UITraceDataRepositoryIterator.hpp"


/**
 *
 */
CUITraceDataRepository::CUITraceDataRepository() : Nyx::CMTInterfaceAccess<CUITraceDataRepository, IUITraceDataRepository>()
{
	m_pLastPos = new CUITraceDataRepositoryIterator(*this);
	m_pLastPos->m_Pos = m_Traces.end();
	m_pLastPos->m_Index = m_Traces.empty() ? -1 : m_Traces.size();

	m_pHeadPos = new CUITraceDataRepositoryIterator(*this);
	m_pHeadPos->m_Pos = m_Traces.end();
	m_pHeadPos->m_Index = m_Traces.empty() ? -1 : m_Traces.size();
}


/**
 *
 */
CUITraceDataRepository::~CUITraceDataRepository()
{
	delete m_pHeadPos;
	delete m_pLastPos;
}


/**
 *
 */
const CUITraceDataRepositoryIterator& CUITraceDataRepository::HeadPos() const
{
	return *m_pHeadPos;
}


/**
 *
 */
const CUITraceDataRepositoryIterator& CUITraceDataRepository::TailPos() const
{
	return *m_pLastPos;
}


/**
 *
 */
size_t CUITraceDataRepository::Count() const
{
	return m_Traces.size();
}


/**
 *
 */
CUITraceData* CUITraceDataRepository::Get( const CUITraceDataRepositoryIterator& pos ) const
{
	return *pos.m_Pos;
}


/**
 *
 */
void CUITraceDataRepository::Add( CUITraceData* pTraceData )
{
	m_Traces.push_back(pTraceData);

	m_pHeadPos->m_Pos = m_Traces.begin();
	m_pHeadPos->m_Index = 0;

	m_pLastPos->m_Index = m_Traces.size();
}
