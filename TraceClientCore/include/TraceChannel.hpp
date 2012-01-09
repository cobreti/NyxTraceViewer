#ifndef _TRACECHANNEL_HPP_
#define _TRACECHANNEL_HPP_


#include <Nyx.hpp>

namespace TraceClientCore
{
    class CTraceData;
    class CTracesPool;
    
    /**
     *
     */
    class CTraceChannel
    {
    public:
        CTraceChannel( CTracesPool* pPool );
        virtual ~CTraceChannel();
        
        const Nyx::CAString&        Name() const        { return m_Name; }
        Nyx::CAString&              Name()              { return m_Name; }
        
        CTracesPool*                Pool() const        { return m_pPool; }
        
        void Insert(CTraceData* pTraceData);
        
    protected:
        
        Nyx::CAString               m_Name;
        CTracesPool*                m_pPool;
    };
}


#endif // _TRACECHANNEL_HPP_
