#include "TraceDataReposLinksCollection.hpp"


/**
 *
 */
CTraceDataReposLinksCollection::CTraceDataReposLinksCollection() :
CTraceDataReposLinkBase()
{
}


/**
 *
 */
CTraceDataReposLinksCollection::~CTraceDataReposLinksCollection()
{
}


/**
 *
 */
bool CTraceDataReposLinksCollection::Update()
{
	bool						bRet = false;
	TDRLinksList::iterator		iter = m_Links.begin();

	while ( iter != m_Links.end() )
	{
		bRet |= (*iter)->Update();
		++ iter;
	}

	return bRet;
}


/**
 *
 */
void CTraceDataReposLinksCollection::Add( CTraceDataReposLinkBase* pLink )
{
	m_Links.push_back(pLink);
}
