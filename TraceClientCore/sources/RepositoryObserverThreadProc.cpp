#include "RepositoryObserverThreadProc.hpp"
#include "RepositoryObserver.hpp"

/**
 *
 */
TraceClientCore::CRepositoryObserverThreadProc::CRepositoryObserverThreadProc(CRepositoryObserver& rRepositoryObserver) :
m_rRepositoryObserver(rRepositoryObserver),
m_bRunning(false),
m_Timeout(1000)
{
}


/**
 *
 */
TraceClientCore::CRepositoryObserverThreadProc::~CRepositoryObserverThreadProc()
{
    Nyx::CTraceStream(0x0).Write(L"Repository observer thread proc destruction");
}


/**
 *
 */
void TraceClientCore::CRepositoryObserverThreadProc::Run()
{
    Nyx::NyxResult      res;

    m_bRunning = true;
    m_refEvent = Nyx::CEvent::Alloc();

    Nyx::CTraceStream(0x0).Write(L"Repository observer thread proc - starting");

    while ( m_bRunning )
    {
        res = m_refEvent->WaitSignaled(m_Timeout);

        if ( Nyx::Succeeded(res) && m_bRunning )
        {
            CRepositoryObserver::Accessor       ROAccess(m_rRepositoryObserver);

            //Nyx::CTraceStream(0x0).Write(L"Checking repository data...");

			if ( ROAccess )
				ROAccess->ProcessCheck();

			//Nyx::CTraceStream(0x0).Write(L"CRepositoryObserverThreadProc idle");
        }
    }

    Nyx::CTraceStream(0x0).Write(L"Repository observer thread proc - ending");
}


/**
 *
 */
void TraceClientCore::CRepositoryObserverThreadProc::Stop()
{
    Nyx::CTraceStream(0x0).Write(L"Repository observer thread proc - stop request");
 
	m_bRunning  = false;
	m_refEvent->Signal(0);
}





