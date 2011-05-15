#ifndef _TRACEFEEDER_HPP_
#define _TRACEFEEDER_HPP_

#include <Nyx.hpp>

namespace TraceClientCore
{
	DECLARE_OBJECTREF(CTraceFeeder)

	class CTraceInserter;
    class CTracesPool;
	

	/**
	 *
	 */
	class CTraceFeeder : public Nyx::CRefCount_Impl<>
	{
	public:
		CTraceFeeder( CTracesPool* pOwnerPool );
		virtual ~CTraceFeeder();

		virtual void Start() = 0;
		virtual void Stop() = 0;
		virtual bool IsRunning() const = 0;

	protected:
	
		//virtual void SetTraceInserter( CTraceInserter* pTraceInserter );		
		//CTraceInserter* TraceInserter() const	{ return m_pTraceInserter; }

        virtual void SetOwnerPool( CTracesPool* pOwnerPool );
        virtual CTracesPool* GetOwnerPool() const       { return m_pOwnerPool; }
		
	protected:
	
		//CTraceInserter*		m_pTraceInserter;
        CTracesPool*        m_pOwnerPool;
	};
}



#endif // _TRACEFEEDER_HPP_
