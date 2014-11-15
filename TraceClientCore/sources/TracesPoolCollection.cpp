#include "TracesPoolCollection.hpp"


/**
 *
 */
TraceClientCore::CTracesPoolCollection::CTracesPoolCollection()
{
}


/**
 *
 */
TraceClientCore::CTracesPoolCollection::~CTracesPoolCollection()
{
}


/**
 *
 */
void TraceClientCore::CTracesPoolCollection::Add( TraceClientCore::CTracesPool* pPool )
{
	//Nyx::CTString		name = pPool->Name();

	m_TracesPools[pPool->Name()] = pPool;
}


/**
 *
 */
void TraceClientCore::CTracesPoolCollection::Update( TraceClientCore::CTracesPool* pPool )
{
	TracesPoolTable::iterator			pos;
	TraceClientCore::CTracesPoolRef		refPool(pPool);

	for (pos = m_TracesPools.begin(); pos != m_TracesPools.end(); ++pos)
		if ( pos->second == refPool )
		{
			m_TracesPools.erase(pos);
			break;
		}

	Add(refPool);
}


/**
 *
 */
void TraceClientCore::CTracesPoolCollection::Clear()
{
	TracesPoolTable::iterator		it;

	while ( !m_TracesPools.empty() )
	{
		it =  m_TracesPools.begin();
		CTracesPoolRef		refPool = it->second;
		m_TracesPools.erase(it);

		//{
		//	CTraceDataRepository::Accessor			ReposAccess(refPool->Repository());
		//	ReposAccess->Clear();
		//}

	}
}


/**
 *
 */
TraceClientCore::CTracesPool* TraceClientCore::CTracesPoolCollection::operator [] (const QString& poolName)
{
//	Nyx::CWString		name( wszPoolName );

    if ( m_TracesPools.count(poolName) > 0 )
        return m_TracesPools[poolName];

	return 0;
}


/**
 *
 */
void TraceClientCore::CTracesPoolCollection::GetPoolsList(CPoolsList &rList)
{
	TracesPoolTable::const_iterator		pos = m_TracesPools.begin();

	while ( pos != m_TracesPools.end() )
	{
		rList.push_back( CPoolsListItem( (CTracesPool*)pos->second ) );
		++ pos;
	}
}
