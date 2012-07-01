#ifndef _TRACEVIEWERCONNECTION_IMPL_HPP_
#define _TRACEVIEWERCONNECTION_IMPL_HPP_

#include <Windows.h>
#include "TraceViewerConnection.hpp"

namespace Nyx
{
    /**
     *
     */
    class CTraceViewerConnection_Impl : public CTraceViewerConnection
    {
        friend class CTraceViewerConnection;
        
    public:

        static void ReleaseInstance();
        static CTraceViewerConnection& Instance();

    public:
        CTraceViewerConnection_Impl();
        virtual ~CTraceViewerConnection_Impl();

        virtual void Write( const char* szData, ... );
        virtual void Write( const wchar_t* wszData, ... );
        
    protected:
        
        bool LoadConnectionModule();
        bool Loaded() const     { return m_bLoaded; }

    protected:
        typedef void (*PFCTReleaseTraceLink)( const unsigned int& id );
        typedef void (*PFCTWriteTraceA)( const unsigned int& id, const char* szData, va_list args );
        typedef void (*PFCTWriteTraceW)( const unsigned int& id, const wchar_t* wszData, va_list args );
        
    protected:

        HMODULE								m_hModule;
        PFCTReleaseTraceLink				m_pfctReleaseTraceLink;
        PFCTWriteTraceA						m_pfctWriteTraceA;
        PFCTWriteTraceW						m_pfctWriteTraceW;
        unsigned int						m_id;
        bool                                m_bLoaded;

        static CTraceViewerConnection_Impl*		s_pInstance;
    };
    
    
    /**
     *
     */
    class CTraceViewerConnection_Pipe_Ansi_Impl : public CTraceViewerConnection_Impl
    {
    public:
        static void CreateInstance(const char* ModuleName);
        
    public:
        CTraceViewerConnection_Pipe_Ansi_Impl(const char* ModuleName);
    };
    
    
    /**
     *
     */
    class CTraceViewerConnection_Pipe_WChar_Impl : public CTraceViewerConnection_Impl
    {
    public:
        static void CreateInstance(const char* ModuleName);
        
    public:
        CTraceViewerConnection_Pipe_WChar_Impl(const char* ModuleName);
    };


    /**
     *
     */
    class CTraceViewerConnection_TcpIp_Ansi_Impl : public CTraceViewerConnection_Impl
    {
    public:
        static void CreateInstance(const char* ModuleName, const char* addr);
        
    public:
        CTraceViewerConnection_TcpIp_Ansi_Impl(const char* ModuleName, const char* addr);
    };
    


    /**
     *
     */
    class CTraceViewerConnection_TcpIp_WChar_Impl : public CTraceViewerConnection_Impl
    {
    public:
        static void CreateInstance(const char* ModuleName, const char* addr);
        
    public:
        CTraceViewerConnection_TcpIp_WChar_Impl(const char* ModuleName, const char* addr);
    };
}

#endif // _TRACEVIEWERCONNECTION_IMPL_HPP_

