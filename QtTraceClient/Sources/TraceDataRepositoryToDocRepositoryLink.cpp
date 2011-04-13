#include "TraceDataRepositoryToDocRepositoryLink.hpp"
#include "DocTraceDataRepository.hpp"

/**
 *
 */
CTraceDataRepositoryToDocRepositoryLink::CTraceDataRepositoryToDocRepositoryLink(	const TraceClientCore::CTracesPool& rSrcPool, 
																					const TraceClientCore::CTraceDataRepository& rSrcRepos,
                                                                                    CDocTraceDataRepository& rDstRepos ) :
TraceClientCore::CTraceDataRepositoryLink(rSrcRepos),
m_rSrcPool(rSrcPool),
m_rDstRepos(rDstRepos),
m_ReposAccessor(rDstRepos, Nyx::eMTLM_Delayed),
m_Count(0)
{
}


/**
 *
 */
CTraceDataRepositoryToDocRepositoryLink::~CTraceDataRepositoryToDocRepositoryLink()
{
}


/**
 *
 */
bool CTraceDataRepositoryToDocRepositoryLink::Contains( const TraceClientCore::CTracesPool& rPool ) const
{
	return (&rPool == &m_rSrcPool);
}


/**
 *
 */
void CTraceDataRepositoryToDocRepositoryLink::OnBeginUpdate()
{
	m_ReposAccessor.Lock();
}


/**
 *
 */
void CTraceDataRepositoryToDocRepositoryLink::OnEndUpdate()
{
    Nyx::CTraceStream(0x0).Write(L"traces count: %i", m_Count );

	m_ReposAccessor.Unlock();
}


/**
 *
 */
void CTraceDataRepositoryToDocRepositoryLink::OnUpdate(const TraceClientCore::CTraceData* pTraceData)
{
    ++ m_Count;
    m_ReposAccessor->Insert(pTraceData);

	//Nyx::CTraceStream(0x0)
	//		<< Nyx::CTF_Text(refTraceData->TickCount().c_str()) << Nyx::CTF_Text(L" -- ")
	//		<< Nyx::CTF_Text(refTraceData->ThreadId().c_str()) << Nyx::CTF_Text(L" -- ")
	//		<< Nyx::CTF_Text(refTraceData->Data().c_str());
}

