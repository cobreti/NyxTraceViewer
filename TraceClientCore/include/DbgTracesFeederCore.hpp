#ifndef _DBGTRACESFEEDERCORE_HPP_
#define _DBGTRACESFEEDERCORE_HPP_

#include <Nyx.hpp>


namespace TraceClientCore
{
	class CTraceDataRepository;
	class CTraceInserter;
    class CTracesPool;

	/**
	 *
	 */
	class IDbgTracesFeederCore
	{
	public:
	
		virtual void Start() = 0;
		virtual void Stop() = 0;
		virtual void StartFeed( const int& nCount,
								const int& nDelayBetweenTraces ) = 0;
	};
	
	
	/**
	 *
	 */
	class CDbgTracesFeederCore : public Nyx::CMTInterfaceAccess<CDbgTracesFeederCore, IDbgTracesFeederCore>
	{
	public:
		CDbgTracesFeederCore(CTracesPool* pOwnerPool, CTraceInserter* pTraceInserter);
		virtual ~CDbgTracesFeederCore();
		
	protected:	// IDbgTracesFeeder methods
	
		virtual void Start();
		virtual void Stop();
		virtual void StartFeed( const int& nCount,
								const int& nDelayBetweenTraces );
	
	protected:	// protected methods
		
		virtual void Thread_RunningLoop();
		virtual void Thread_StopRequest();
		
	protected:
	
		Nyx::CThreadRef								m_refThread;
		Nyx::CEventRef								m_refEvent;
		bool										m_bFeedCancelled;
		int											m_TracesCounter;
		
		int											m_nTracesCount;
		int											m_nDelayBetweenTraces;
		
		CTraceInserter*								m_pTraceInserter;
        CTracesPool*                                m_pOwnerPool;
	};
}


#endif // _DBGTRACESFEEDERCORE_HPP_
