#ifndef _TRACEDATAREPOSITORYLINKCOLLECTION_HPP_
#define _TRACEDATAREPOSITORYLINKCOLLECTION_HPP_

#include "TraceDataRepositoryLinkBase.hpp"

#include <list>

namespace TraceClientCore
{
	class CTraceDataRepositoryLinkCollection : public CTraceDataRepositoryLinkBase
	{
	public:
		CTraceDataRepositoryLinkCollection();
		virtual ~CTraceDataRepositoryLinkCollection();
		
		virtual bool Update(CTraceInserter* pTraceInserter);
		
		virtual void Add( CTraceDataRepositoryLinkBase* pLink );
		virtual void Remove( CTraceDataRepositoryLinkBase* pLink );
		virtual bool Contains( const CTracesPool& rPool ) const;
		virtual CTraceDataRepositoryLinkBase* GetLinkContains( const CTracesPool& rPool ) const;
		
	protected:
	
		typedef		std::list<CTraceDataRepositoryLinkBaseRef>		LinksList;
		
	protected:
	
		LinksList		m_Links;
	};
}


#endif // _TRACEDATAREPOSITORYLINKCOLLECTION_HPP_
