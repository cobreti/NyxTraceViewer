#ifndef _TRACELINK_HPP_
#define _TRACELINK_HPP_

#include "Nyx.hpp"
#include "NyxNet.hpp"

#include <map>

/**
 *
 */
class CTraceLink
{
public:
    CTraceLink();
    ~CTraceLink();

    unsigned int CreateTraceLink_PipeAnsi( const char* szName );
    unsigned int CreateTraceLink_PipeWChar( const char* szName );
    unsigned int CreateTraceLink_TcpAnsi( const char* szName, const char* szAddr );
    unsigned int CreateTraceLink_TcpWChar( const char* szName, const char* szAddr );
    
    void ReleaseTraceLink( const unsigned int& id );
    void WriteTraceA( const unsigned int& id, const char* szData, va_list args );
    void WriteTraceW( const unsigned int& id, const wchar_t* wszData, va_list args );

protected:

    typedef		std::map<unsigned int, Nyx::CTraceCompositorRef>			TraceCompositorsMap;

    enum
    {
        kBufferSize = 8192
    };

protected:


    Nyx::CMutexRef                          m_refMutex;
    Nyx::CModuleRef							m_refModule;
    Nyx::CTraceCompositorRef				m_refTraceCompositor;
    TraceCompositorsMap						m_TraceCompositorsTable;
    unsigned int							m_NextAvailID;

    Nyx::CAString							m_AnsiBuffer;
    Nyx::CWString							m_WCharBuffer;
};


#endif // _TRACELINK_HPP_
