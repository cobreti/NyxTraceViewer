#ifndef _TRACENXSTREAMREADER_HPP_
#define _TRACENXSTREAMREADER_HPP_

#include <Nyx.hpp>

namespace NyxNet
{
    class INxStreamRW;
}

namespace TraceClientCore
{
    class CTracesPool;
    class CTraceData;
    
    class CTraceNxStreamReader
    {
    public:
        CTraceNxStreamReader( CTracesPool* pPool );
        ~CTraceNxStreamReader();
        
        virtual CTraceData* Read( NyxNet::INxStreamRW& rStream );
        
    protected:
		Nyx::TBuffer<Nyx::Byte>		m_ReadBuffer;
        CTracesPool*                m_pPool;
    };
}


#endif // _TRACENXSTREAMREADER_HPP_
