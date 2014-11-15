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
    m_refPool(pPool)
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
        pTraceData->Channel() = this;
        m_refPool->Repository().Insert(pTraceData);
    }

    
    /**
     *
     */
    void CTraceChannel::Clear()
    {
        m_refPool->Repository().Clear(m_Name);
		m_refPool->MemoryPool()->Clear();
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
