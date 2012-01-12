#ifndef _TRACEFEEDER_HPP_
#define _TRACEFEEDER_HPP_

#include <Nyx.hpp>

namespace TraceClientCore
{
	DECLARE_OBJECTREF(CTraceFeeder)

	class CTraceInserter;
    class CTracesPool;
    class CTraceChannel;
	

	/**
	 *
	 */
	class CTraceFeeder : public Nyx::CRefCount_Impl<>
	{
	public:
		CTraceFeeder( CTraceChannel* pChannel );
		virtual ~CTraceFeeder();

		virtual void Start() = 0;
		virtual void Stop() = 0;
		virtual bool IsRunning() const = 0;

	protected:
	        
        virtual CTraceChannel*      Channel() const     { return m_pChannel; }
		
	protected:
	
        CTraceChannel*          m_pChannel;
	};
}



#endif // _TRACEFEEDER_HPP_
