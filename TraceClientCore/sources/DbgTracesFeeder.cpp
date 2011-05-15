#include "DbgTracesFeeder.hpp"


namespace TraceClientCore
{
    /**
     *
     */
    CDbgTracesFeeder::CDbgTracesFeeder( CTracesPool* pOwnerPool ) :
    CTraceFeeder(pOwnerPool)
    //m_Core(pOwnerPool, pTraceInserter)
    {
    }


    /**
     *
     */
    TraceClientCore::CDbgTracesFeeder::~CDbgTracesFeeder()
    {
        Stop();
    }


    /**
     *
     */
    void TraceClientCore::CDbgTracesFeeder::Start()
    {
    //	CDbgTracesFeederCore::Accessor		FeederAccess(m_Core);
    //	
    //	FeederAccess->Start();
    }


    /**
     *
     */
    void TraceClientCore::CDbgTracesFeeder::Stop()
    {
    //	CDbgTracesFeederCore::Accessor		FeederAccess(m_Core);
    //	
    //	FeederAccess->Stop();
    }


    /**
     *
     */
    void TraceClientCore::CDbgTracesFeeder::StartFeed(	const int& nCount,
                                                        const int& nDelayBetweenTraces )
    {
    //	CDbgTracesFeederCore::Accessor		FeederAccess(m_Core);
    //	
    //	FeederAccess->StartFeed(nCount, nDelayBetweenTraces);
    }


    /**
     *
     */
    bool TraceClientCore::CDbgTracesFeeder::IsRunning() const
    {
        return true;
    }
}

