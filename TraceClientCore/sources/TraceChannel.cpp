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
    }
    
    
    /**
     *
     */
    void CTraceChannel::Insert(CTraceData* pTraceData)
    {
        Nyx::CTraceStream(0x0)  << Nyx::CTF_Text(L"Trace : « ") << Nyx::CTF_Text(pTraceData->Data().c_str()) << Nyx::CTF_Text(L" »");
        
        m_pPool->Repository().Insert(pTraceData);
    }
}
