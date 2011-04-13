#include "TraceDataRepositoryLink.hpp"
#include "TraceInserter.hpp"

/**
 *
 */
TraceClientCore::CTraceDataRepositoryLink::CTraceDataRepositoryLink( const TraceClientCore::CTraceDataRepository& rSrcRepos ) :
TraceClientCore::CTraceDataRepositoryLinkBase(),
m_rSrcRepos(rSrcRepos),
m_hLastEndPos(NULL)
{
}


/**
 *
 */
TraceClientCore::CTraceDataRepositoryLink::~CTraceDataRepositoryLink()
{
	CTraceDataRepository::ConstAccessor		Access(m_rSrcRepos);
	
	Access->ReleaseIterator(m_hLastEndPos);
}


/**
 *
 */
bool TraceClientCore::CTraceDataRepositoryLink::Update(CTraceInserter* pTraceInserter)
{
	bool									bChanges = false;
	ITraceDataRepository::IteratorHandle	hNewEndPos;
	CTraceDataRepository::ConstAccessor		ReposAccess(m_rSrcRepos);
	CTraceData*								pTrace = NULL;
	
	if ( ReposAccess->TracesCount() == 0 )
		return false;

	OnBeginUpdate();
	
	hNewEndPos = ReposAccess->AllocIterator();
	ReposAccess->GetTailPos(hNewEndPos);
	ReposAccess->DecrIterator(hNewEndPos);
	
    if ( NULL == m_hLastEndPos )
    {
        m_hLastEndPos = ReposAccess->AllocIterator();
        ReposAccess->GetHeadPos(m_hLastEndPos);
		bChanges = true;
    }
	else
	{		
		bChanges = !ReposAccess->AreEqual(m_hLastEndPos, hNewEndPos);
		if ( bChanges )
			ReposAccess->IncrIterator(m_hLastEndPos);
	}

	if ( bChanges )
	{
		while ( !UpdateCancelled() && !ReposAccess->AreEqual(m_hLastEndPos, hNewEndPos) )
		{
			pTrace = ReposAccess->Get(m_hLastEndPos);
			
			//OnUpdate(pTrace);
            pTraceInserter->Insert(pTrace);

			ReposAccess->IncrIterator(m_hLastEndPos);
		}

		pTrace = ReposAccess->Get(m_hLastEndPos);

//		OnUpdate(pTrace);
        pTraceInserter->Insert(pTrace);
	}
	
		
	ReposAccess->ReleaseIterator(hNewEndPos);

	OnEndUpdate();
	
	return bChanges;
}


/**
 *
 */
void TraceClientCore::CTraceDataRepositoryLink::OnBeginUpdate()
{
}


/**
 *
 */
void TraceClientCore::CTraceDataRepositoryLink::OnEndUpdate()
{
}


/**
 *
 */
//void TraceClientCore::CTraceDataRepositoryLink::OnUpdate(const TraceClientCore::CTraceData* rpTraceData)
//{
//}
