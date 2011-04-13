#include "TraceDataRepositoryLinkCollection.hpp"


/**
 *
 */
TraceClientCore::CTraceDataRepositoryLinkCollection::CTraceDataRepositoryLinkCollection() :
CTraceDataRepositoryLinkBase()
{
}


/**
 *
 */
TraceClientCore::CTraceDataRepositoryLinkCollection::~CTraceDataRepositoryLinkCollection()
{
}


/**
 *
 */
bool TraceClientCore::CTraceDataRepositoryLinkCollection::Update(CTraceInserter* pTraceInserter)
{
	bool				bUpdated = false;
	LinksList::iterator	pos = m_Links.begin();
	
	while ( !UpdateCancelled() && pos != m_Links.end() )
	{
		bUpdated |= (*pos)->Update(pTraceInserter);
		++pos;
	}
	
	return bUpdated;
}


/**
 *
 */
void TraceClientCore::CTraceDataRepositoryLinkCollection::Add( CTraceDataRepositoryLinkBase* pLink )
{
	if ( pLink == NULL )
		return;
		
	m_Links.push_back(pLink);
}


/**
 *
 */
void TraceClientCore::CTraceDataRepositoryLinkCollection::Remove( CTraceDataRepositoryLinkBase* pLink )
{
	LinksList::iterator		it;

	for (it = m_Links.begin(); it != m_Links.end(); ++it)
	{
		if ( ((CTraceDataRepositoryLinkBase*)*it) == pLink )
		{
			m_Links.erase(it);
			break;
		}
	}
}


/**
 *
 */
bool TraceClientCore::CTraceDataRepositoryLinkCollection::Contains( const TraceClientCore::CTracesPool& rPool ) const
{
	LinksList::const_iterator		pos;

	for (pos = m_Links.begin(); pos != m_Links.end(); ++pos)
		if ( (*pos)->Contains(rPool) )
			return true;

	return false;
}


/**
 *
 */
TraceClientCore::CTraceDataRepositoryLinkBase* TraceClientCore::CTraceDataRepositoryLinkCollection::GetLinkContains( const TraceClientCore::CTracesPool& rPool ) const
{
	LinksList::const_iterator		pos;

	for (pos = m_Links.begin(); pos != m_Links.end(); ++pos)
		if ( (*pos)->Contains(rPool) )
			return *pos;

	return NULL;
}
