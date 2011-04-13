#include "TracesFeedersCollection.hpp"


/**
 *
 */
CTracesFeedersCollection::CTracesFeedersCollection()
{
}


/**
 *
 */
CTracesFeedersCollection::~CTracesFeedersCollection()
{
}


/**
 *
 */
void CTracesFeedersCollection::Add( CTracesFeeder* pFeeder )
{
	m_TracesFeeders[Nyx::CTString(pFeeder->Name())] = pFeeder;

	CTracesFeeder::Accessor		FeederAccess(*pFeeder);
	
	if (FeederAccess)
		FeederAccess->OnAddedToCollection();
}


/**
 *
 */
void CTracesFeedersCollection::Remove( CTracesFeeder* pFeeder )
{
	TracesFeedersTable::iterator	pos = m_TracesFeeders.find(pFeeder->Name()->CStr());
	CTracesFeederRef				refFeeder;

	if ( pos != m_TracesFeeders.end() )
	{
		refFeeder = pos->second;
		m_TracesFeeders.erase(pos);
		CTracesFeeder::Accessor			FeederAccess(*refFeeder);
		
		if (FeederAccess)
			FeederAccess->OnRemovedFromCollection();
	}
}


/**
 *
 */
void CTracesFeedersCollection::Clear()
{
	TracesFeedersTable::iterator	pos;
	CTracesFeederRef				refFeeder;

	while ( !m_TracesFeeders.empty() )
	{
		pos = m_TracesFeeders.begin();

		refFeeder = pos->second;
		m_TracesFeeders.erase(pos);
		
		{
			CTracesFeeder::Accessor		FeederAccess(refFeeder);
			
			if (FeederAccess)
				FeederAccess->OnRemovedFromCollection();
		}

		refFeeder = NULL;
	}
}



/**
 *
 */
CTracesFeeder* CTracesFeedersCollection::Get( const wchar_t* wszName )
{
	return m_TracesFeeders[wszName];
}
