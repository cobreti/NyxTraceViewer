#include "DbgTracesFeederCore.hpp"
#include "TraceDataRepository.hpp"
#include "TraceInserter.hpp"
#include "TracesPool.hpp"

/**
 *
 */
TraceClientCore::CDbgTracesFeederCore::CDbgTracesFeederCore(CTracesPool* pOwnerPool, TraceClientCore::CTraceInserter* pTraceInserter) :
m_bFeedCancelled(false),
m_TracesCounter(0),
m_nTracesCount(0),
m_nDelayBetweenTraces(0),
m_pTraceInserter(pTraceInserter),
m_pOwnerPool(pOwnerPool)
{
}


/**
 *
 */
TraceClientCore::CDbgTracesFeederCore::~CDbgTracesFeederCore()
{
	//Stop();
}


/**
 *
 */
void TraceClientCore::CDbgTracesFeederCore::Start()
{
	m_refEvent = Nyx::CEvent::Alloc();

	m_refThread = Nyx::CThread::Alloc();
	m_refThread->Start( new Nyx::CThreadDelegateNoRef<TraceClientCore::CDbgTracesFeederCore>(this,
							&TraceClientCore::CDbgTracesFeederCore::Thread_RunningLoop,
							&TraceClientCore::CDbgTracesFeederCore::Thread_StopRequest ) );
}


/**
 *
 */
void TraceClientCore::CDbgTracesFeederCore::Stop()
{
	Nyx::CTraceStream(0x0).Write(L"CDbgTracesFeederCore::Stop - starting");
	m_refThread->Stop();
	m_refThread = NULL;
	Nyx::CTraceStream(0x0).Write(L"CDbgTracesFeederCore::Stop - ending");
}


/**
 *
 */
void TraceClientCore::CDbgTracesFeederCore::StartFeed(	const int& nCount,
														const int& nDelayBetweenTraces )
{
	m_nTracesCount = nCount;
	m_nDelayBetweenTraces = nDelayBetweenTraces;
	
	if ( m_refEvent.Valid() )
		m_refEvent->Signal(0);
}



/**
 *
 */
void TraceClientCore::CDbgTracesFeederCore::Thread_RunningLoop()
{
	Nyx::CTraceStream(0x0).Write(L"Starting Dbg Traces Feeder core thread");

    TraceClientCore::CTraceData*				pTraceData = NULL;
    Nyx::CWString                               TickCount;
    
    TickCount.Reserve(1024);
    //Nyx::CStringFormaterRef                     refStringFormater = Nyx::CStringFormater::Alloc(1024);

	while ( !m_bFeedCancelled )
	{
		m_nTracesCount = 0;
		m_nDelayBetweenTraces = 0;
		
		m_refEvent->WaitSignaled();
		
		if ( !m_bFeedCancelled )
		{			
			while ( !m_bFeedCancelled && m_nTracesCount-- > 0 )
			{				
				pTraceData = new (m_pOwnerPool->MemoryPool()) TraceClientCore::CTraceData(m_pOwnerPool->MemoryPool());
				pTraceData->Data() = L"test trace data";
				pTraceData->ThreadId() = L"thread id";
                pTraceData->OwnerPool() = m_pOwnerPool;

				//refStringFormater->Format(L"%i", m_TracesCounter++);
                TickCount.Format(L"%i", m_TracesCounter++);
				pTraceData->TickCount() = TickCount.c_str(); //refStringFormater->GetFormattedString();

				m_pTraceInserter->Insert(pTraceData);

				Nyx::CSystem().Sleep(m_nDelayBetweenTraces);
			}
		}
	}

	Nyx::CTraceStream(0x0).Write(L"Dbg Traces Feeder core thread terminating");
}


/**
 *
 */
void TraceClientCore::CDbgTracesFeederCore::Thread_StopRequest()
{
	m_bFeedCancelled = true;
	
	if ( m_refEvent.Valid() )
		m_refEvent->Signal(0);
}

