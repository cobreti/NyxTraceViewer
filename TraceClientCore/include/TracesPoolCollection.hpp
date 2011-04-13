#ifndef _TRACESPOOLCOLLECTION_HPP_
#define _TRACESPOOLCOLLECTION_HPP_

#include "TracesPool.hpp"
#include "DataStruct/PoolsList.hpp"

#include <map>

namespace TraceClientCore
{
	class CTracesPoolCollection
	{
	public:
		CTracesPoolCollection();
		virtual ~CTracesPoolCollection();
		
		virtual void Add( CTracesPool* pPool );
		virtual void Update( CTracesPool* pPool );
		virtual void Clear();
		
		CTracesPool* operator [] ( const wchar_t* wszPoolName );

		void GetPoolsList( CPoolsList& rList );
		
	protected: // protected types
	
		typedef		std::map<const Nyx::CWString, CTracesPoolRef>		TracesPoolTable;
		
	protected: // protected members
	
		TracesPoolTable			m_TracesPools;
	};
}


#endif // _TRACESPOOLCOLLECTION_HPP_
