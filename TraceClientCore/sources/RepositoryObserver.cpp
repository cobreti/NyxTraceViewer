#include "RepositoryObserver.hpp"
#include "RepositoryObserverThreadProc.hpp"


/**
 *
 */
TraceClientCore::CRepositoryObserver::CRepositoryObserver() :
m_bStopping(false)
{
}


/**
 *
 */
TraceClientCore::CRepositoryObserver::~CRepositoryObserver()
{
	Nyx::CTraceStream(0x0).Write(L"CRepositoryObserver::~CRepositoryObserver");
    //Stop();
}


/**
 *
 */
void TraceClientCore::CRepositoryObserver::Start()
{
    m_refThread = Nyx::CThread::Alloc();
    m_refThread->Start( new TraceClientCore::CRepositoryObserverThreadProc(*this) );
}


/**
 *
 */
void TraceClientCore::CRepositoryObserver::Stop()
{
	m_bStopping = true;
	m_RepositoryLinks.CancelUpdate();
	if ( m_refThread.Valid() )
	{
		m_refThread->Stop();
		m_refThread = NULL;
	}
	m_bStopping = false;

	Nyx::CTraceStream(0x0).Write(L"CRepositoryObserver::Stop - ending");
}


/**
 *
 */
void TraceClientCore::CRepositoryObserver::ProcessCheck()
{
    CTraceInserter* pTraceInserter = m_refNotificationsHandler->OnBeginCheckUpdate();
    
    if ( Links().Update(pTraceInserter) && m_refNotificationsHandler.Valid() )
    {
		m_refNotificationsHandler->OnNewItems();
    }
    
    m_refNotificationsHandler->OnEndCheckUpdate();
}


/**
 *
 */
TraceClientCore::CRepositoryObserverNotificationsHandlerRef& TraceClientCore::CRepositoryObserver::NotificationsHandler()
{
	return m_refNotificationsHandler;
}


/**
 *
 */
TraceClientCore::CRepositoryObserverNotificationsHandlerRef TraceClientCore::CRepositoryObserver::NotificationsHandler() const
{
	return m_refNotificationsHandler;
}



