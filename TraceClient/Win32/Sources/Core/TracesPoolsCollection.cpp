#include "TracesPoolsCollection.hpp"


/**
 *
 */
CTracesPoolsCollection::CTracesPoolsCollection()
{
}


/** 
 *
 */
CTracesPoolsCollection::~CTracesPoolsCollection()
{
}


/**
 *
 */
void CTracesPoolsCollection::Add( CTracesPool* pPool )
{
	m_TracesPools[Nyx::CTString(pPool->Name())] = pPool;
}


CTracesPool* CTracesPoolsCollection::operator [] ( const wchar_t* wszPoolName )
{
	return m_TracesPools[wszPoolName];
}
