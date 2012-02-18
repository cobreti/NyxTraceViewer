#include "TraceChannel.hpp"
#include "TracesPool.hpp"
#include "TraceDataRepository.hpp"
#include "TraceData.hpp"

namespace TraceClientCore
{
    /**
     *
     */
    CTraceChannel::CTraceChannel(CTracesPool* pPool) :
    m_pPool(pPool)
    {
        
    }
    
    
    /**
     *
     */
    CTraceChannel::~CTraceChannel()
    {
        m_refFeeder.Release();
    }
    
    
    /**
     *
     */
    void CTraceChannel::Insert(CTraceData* pTraceData)
    {        
        m_pPool->Repository().Insert(pTraceData);
    }

    
    /**
     *
     */
    void CTraceChannel::Stop()
    {
        if ( m_refFeeder.Valid() && m_refFeeder->IsRunning() )
            m_refFeeder->Stop();
    }
}
