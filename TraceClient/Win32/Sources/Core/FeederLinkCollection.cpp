#include "FeederLinkCollection.hpp"


/**
 *
 */
CFeederLinkCollection::CFeederLinkCollection() : CFeederLink()
{
}


/**
 *
 */
CFeederLinkCollection::~CFeederLinkCollection()
{
}


/**
 *
 */
void CFeederLinkCollection::Add(CFeederLink *pFeederLink)
{
	m_FeederLinks.push_back(pFeederLink);
}


/**
 *
 */
void CFeederLinkCollection::Remove(CFeederLink* pFeederLink)
{
	m_FeederLinks.remove(pFeederLink);
}


/**
 *
 */
void CFeederLinkCollection::Feed( CTraceData* pTraceData )
{
	FeederLinkList::iterator	pos = m_FeederLinks.begin();

	while ( pos != m_FeederLinks.end() )
	{
		(*pos)->Feed(pTraceData);
		++ pos;
	}
}

