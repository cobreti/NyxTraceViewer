#include "TraceDataReposLink.hpp"
#include "TraceDataReposIterator.hpp"
#include "UITraceDataRepository.hpp"


/**
 *
 */
CTraceDataReposLink::CTraceDataReposLink(CTraceDataRepos &rRepository, CUITraceDataRepository& rUIRepository) :
CTraceDataReposLinkBase(),
m_rRepository(rRepository),
m_rUIRepository(rUIRepository),
m_pSrcLastEndPos(NULL)
{
}


/**
 *
 */
CTraceDataReposLink::~CTraceDataReposLink()
{
}


/**
 *
 */
bool CTraceDataReposLink::Update()
{
	bool		bUpdatedData = false;

	CTraceDataRepos::ConstAccessor		SrcReposAccessor(m_rRepository);
	CTraceDataReposIterator				Pos(m_rRepository);
	CTraceDataReposIterator::Accessor	PosAccessor(Pos);
	CTraceDataReposIterator				LastPos(m_rRepository);
	CTraceDataReposIterator::Accessor	LastPosAccessor(LastPos);
	CTraceData*							pTraceData = NULL;
	CUITraceDataRepository::Accessor	UIReposAccessor(m_rUIRepository);
	CUITraceData*						pUITraceData = NULL;

	if ( SrcReposAccessor->IsEmpty() )
		return false;

	if ( m_pSrcLastEndPos == NULL )
	{
		m_pSrcLastEndPos = new CTraceDataReposIterator(m_rRepository);
		Pos = SrcReposAccessor->HeadPos();
	}
	else
	{
		PosAccessor= *m_pSrcLastEndPos;
		++ PosAccessor;
	}

	if ( PosAccessor != SrcReposAccessor->TailPos() )
	{
		bUpdatedData = true;

		LastPosAccessor = SrcReposAccessor->TailPos();
		-- LastPosAccessor;

		while ( PosAccessor != LastPosAccessor )
		{
			pTraceData = SrcReposAccessor->Get(PosAccessor);

			pUITraceData = new CUITraceData(pTraceData);
			UIReposAccessor->Add( pUITraceData );

			//Nyx::CTraceStream(0x0)
			//	<< Nyx::CTF_Text(L"[")
			//	<< Nyx::CTF_Text( pTraceData->ThreadId()->CStr() )
			//	<< Nyx::CTF_Text(L"] [")
			//	<< Nyx::CTF_Text( pTraceData->TickCount()->CStr() )
			//	<< Nyx::CTF_Text(L" | ")
			//	<< Nyx::CTF_Text( pTraceData->Data()->CStr() );

			++ PosAccessor;
		}

		pTraceData = SrcReposAccessor->Get(PosAccessor);
		pUITraceData = new CUITraceData(pTraceData);
		UIReposAccessor->Add( pUITraceData );

		//Nyx::CTraceStream(0x0)
		//	<< Nyx::CTF_Text(L"[")
		//	<< Nyx::CTF_Text( pTraceData->ThreadId()->CStr() )
		//	<< Nyx::CTF_Text(L"] [")
		//	<< Nyx::CTF_Text( pTraceData->TickCount()->CStr() )
		//	<< Nyx::CTF_Text(L" | ")
		//	<< Nyx::CTF_Text( pTraceData->Data()->CStr() );


		*m_pSrcLastEndPos = PosAccessor;
	}

	return bUpdatedData;
}


