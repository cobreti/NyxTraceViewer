#ifndef _TRACEDATAREPOSITORYLINKBASE_HPP_
#define _TRACEDATAREPOSITORYLINKBASE_HPP_

#include <Nyx.hpp>
#include <NyxRefCount_Impl.hpp>

namespace TraceClientCore
{
	DECLARE_OBJECTREF(CTraceDataRepositoryLinkBase)

	class CTracesPool;
    class CTraceInserter;
	
	class CTraceDataRepositoryLinkBase : public Nyx::CRefCount_Impl<>
	{
	public:
		CTraceDataRepositoryLinkBase();
		virtual ~CTraceDataRepositoryLinkBase();
		
		virtual bool Update(CTraceInserter* pTraceInserter);
		virtual void CancelUpdate();
		virtual bool UpdateCancelled() const { return m_bUpdateCancelled; }
		virtual bool Contains( const CTracesPool& rPool ) const;
		
	protected:
	
		bool		m_bUpdateCancelled;
	};
}


#endif // _TRACEDATAREPOSITORYLINKBASE_HPP_
