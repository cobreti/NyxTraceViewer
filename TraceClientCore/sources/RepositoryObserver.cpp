#include "RepositoryObserver.hpp"
//#include "RepositoryObserverThreadProc.hpp"
#include "DataStruct/TracesCollection.hpp"

namespace TraceClientCore
{
    /**
     *
     */
    CRepositoryObserver::CRepositoryObserver() :
    m_UpdatesCounter(0)
    {
    }


    /**
     *
     */
    CRepositoryObserver::~CRepositoryObserver()
    {
	    Nyx::CTraceStream(0x0).Write(L"CRepositoryObserver::~CRepositoryObserver");
    }


    /**
     *
     */
    void CRepositoryObserver::BeginUpdate()
    {
        if ( m_UpdatesCounter == 0 )
            OnFirstBeginUpdate();

        ++ m_UpdatesCounter;
    }


    /**
     *
     */
    void CRepositoryObserver::EndUpdate()
    {
        if ( --m_UpdatesCounter == 0 )
            OnFinalEndUpdate();
    }

    /**
     *
     */
    void CRepositoryObserver::Insert( CTraceData* pTraceData )
    {
    }


    /**
     *
     */
    void CRepositoryObserver::OnFirstBeginUpdate()
    {
    }


    /**
     *
     */
    void CRepositoryObserver::OnFinalEndUpdate()
    {
    }
}
