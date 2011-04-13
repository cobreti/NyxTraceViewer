#include "TraceDataRepos.hpp"
#include "TraceDataReposIterator.hpp"
#include <NyxLock.hpp>


/**
 *
 */
CTraceDataRepos::CTraceDataRepos() :
Nyx::CMTInterfaceAccess<CTraceDataRepos, ITraceDataRepos>(),
m_pHeadPos(NULL),
m_pTailPos(NULL),
m_AddedTraces(0)
{
}


/**
 *
 */
CTraceDataRepos::~CTraceDataRepos()
{
	if ( m_pTailPos == NULL )
		delete m_pTailPos;

	if ( m_pHeadPos == NULL )
		delete m_pHeadPos;
}


void CTraceDataRepos::OnMTLastWriteUnlock()
{
	//Nyx::CTraceStream(0x0).Write(L"Last unlock : sending update if data was inserted");
	if ( m_AddedTraces > 0 )
	{
		m_AddedTraces = 0;
	}
}


/** 
 *
 */
size_t CTraceDataRepos::Count() const
{
	return m_TracesData.size();
}


/**
 *
 */
void CTraceDataRepos::Add( CTraceData* pTraceData )
{
	if ( pTraceData == NULL )
		return;

	m_TracesData.push_back(pTraceData);
	++ m_AddedTraces;

	if ( m_pTailPos == NULL )
		m_pTailPos = new CTraceDataReposIterator(*this);
	else
		++ m_pTailPos->m_Index;

	if ( m_pHeadPos == NULL )
	{
		m_pHeadPos = new CTraceDataReposIterator(*this);
		m_pHeadPos->m_Pos = m_TracesData.begin();
	}
}


/**
 *
 */
const CTraceDataReposIterator& CTraceDataRepos::HeadPos() const
{
	return *m_pHeadPos;
}


/**
 *
 */
const CTraceDataReposIterator& CTraceDataRepos::TailPos() const
{
	return *m_pTailPos;
}


/**
 *
 */
bool CTraceDataRepos::IsEmpty() const
{
	return m_TracesData.empty();
}


/**
 *
 */
CTraceData* CTraceDataRepos::Get( const CTraceDataReposIterator& pos ) const
{
	if ( &(pos.m_rRepos) != this )
		return NULL;

	if ( pos.m_Pos == m_TracesData.end() )
		return NULL;

	return *pos.m_Pos;
}


