#include "TraceViewerConnection_Impl.hpp"

#include <stdio.h>


namespace Nyx
{
    /**
     *
     */
    class CDummyTraceViewerConnection : public CTraceViewerConnection
    {
    public:
       CDummyTraceViewerConnection() {};
       virtual ~CDummyTraceViewerConnection() {};

       virtual void Write( const char* szData, ... ) {}
       virtual void Write( const wchar_t* wszData, ... ) {}

    };


    /**
     *
     */
    CTraceViewerConnection_Impl*			CTraceViewerConnection_Impl::s_pInstance = NULL;

    static CDummyTraceViewerConnection      s_DummyTraceViewerConnection;


    /**
     *
     */
    void CTraceViewerConnection_Pipe_Ansi::CreateInstance(const char* ModuleName)
    {
        CTraceViewerConnection_Pipe_Ansi_Impl::CreateInstance(ModuleName);
    }
    

    /**
     *
     */
    void CTraceViewerConnection_Pipe_WChar::CreateInstance(const char* ModuleName)
    {
        CTraceViewerConnection_Pipe_WChar_Impl::CreateInstance(ModuleName);
    }
    
    
    /**
     *
     */
    void CTraceViewerConnection_TcpIp_Ansi::CreateInstance(const char* ModuleName, const char* addr)
    {
        CTraceViewerConnection_TcpIp_Ansi_Impl::CreateInstance(ModuleName, addr);
    }
    
    
    /**
     *
     */
    void CTraceViewerConnection_TcpIp_WChar::CreateInstance(const char* ModuleName, const char* addr)
    {
        CTraceViewerConnection_TcpIp_WChar_Impl::CreateInstance(ModuleName, addr);
    }
    
    
    /**
     *
     */
    void CTraceViewerConnection::ReleaseInstance()
    {
        CTraceViewerConnection_Impl::ReleaseInstance();
    }


    /**
     *
     */
    CTraceViewerConnection& CTraceViewerConnection::Instance()
    {
        return CTraceViewerConnection_Impl::Instance();
    }


    /**
     *
     */
    void CTraceViewerConnection_Impl::ReleaseInstance()
    {
       if ( s_pInstance != NULL )
       {
           delete s_pInstance;
          s_pInstance = NULL;
       }
    }


    /**
     *
     */
    CTraceViewerConnection& CTraceViewerConnection_Impl::Instance()
    {
       if ( s_pInstance != NULL )
           return *s_pInstance;

       return s_DummyTraceViewerConnection;
    }


    /**
     *
     */
    CTraceViewerConnection_Impl::CTraceViewerConnection_Impl() :
    m_hModule(NULL),
    m_pfctReleaseTraceLink(NULL),
    m_pfctWriteTraceA(NULL),
    m_pfctWriteTraceW(NULL),
    m_id(0),
    m_bLoaded(false)
    {
        LoadConnectionModule();
    }


    /**
     *
     */
    CTraceViewerConnection_Impl::~CTraceViewerConnection_Impl()
    {
        if ( m_id > 0 && m_pfctReleaseTraceLink )
            m_pfctReleaseTraceLink(m_id);

        if ( m_hModule )
        {
            ::FreeLibrary(m_hModule);
        }
    }


    /**
     *
     */
    void CTraceViewerConnection_Impl::Write(const char* szData, ...)
    {
        if ( m_id > 0 && m_pfctWriteTraceA )
        {
            va_list args;
            va_start(args, szData);
            m_pfctWriteTraceA(m_id, szData, args);
            va_end(args);
        }
    }


    /**
     *
     */
    void CTraceViewerConnection_Impl::Write( const wchar_t* wszData, ... )
    {
        if ( m_id > 0 && m_pfctWriteTraceW )
        {
            va_list args;
            va_start(args, wszData);
            m_pfctWriteTraceW(m_id, wszData, args);
            va_end(args);
        }
    }


    /**
     *
     */
    bool CTraceViewerConnection_Impl::LoadConnectionModule()
    {
        m_hModule = ::LoadLibraryA("NyxTraceViewerConnection.dll");
        if ( m_hModule )
        {
            m_pfctReleaseTraceLink = (PFCTReleaseTraceLink)::GetProcAddress(m_hModule, "ReleaseTraceLink");
            m_pfctWriteTraceA = (PFCTWriteTraceA)::GetProcAddress(m_hModule, "WriteTraceA");
            m_pfctWriteTraceW = (PFCTWriteTraceW)::GetProcAddress(m_hModule, "WriteTraceW");
            m_bLoaded = true;
        }

        return true;
    }
    
    
    /**
     *
     */
    void CTraceViewerConnection_Pipe_Ansi_Impl::CreateInstance(const char* ModuleName)
    {
        if ( s_pInstance == NULL )
            s_pInstance = new CTraceViewerConnection_Pipe_Ansi_Impl(ModuleName);
    }

    
    /**
     *
     */
    CTraceViewerConnection_Pipe_Ansi_Impl::CTraceViewerConnection_Pipe_Ansi_Impl(const char* ModuleName) : CTraceViewerConnection_Impl()
    {
        typedef unsigned int (*PFCTCreateConnection)(const char* szName);
        
        if ( Loaded() )
        {
            PFCTCreateConnection  pfctCreateConnection = (PFCTCreateConnection)::GetProcAddress(m_hModule, "CreateTraceLink_PipeAnsi");

            if ( pfctCreateConnection )
                m_id = pfctCreateConnection(ModuleName);
        }
    }

    
    /**
     *
     */
    void CTraceViewerConnection_Pipe_WChar_Impl::CreateInstance(const char* ModuleName)
    {
        if ( s_pInstance == NULL )
            s_pInstance = new CTraceViewerConnection_Pipe_WChar_Impl(ModuleName);
    }
    
    
    /**
     *
     */
    CTraceViewerConnection_Pipe_WChar_Impl::CTraceViewerConnection_Pipe_WChar_Impl(const char* ModuleName) : CTraceViewerConnection_Impl()
    {
        typedef unsigned int (*PFCTCreateConnection)(const char* szName);
        
        if ( Loaded() )
        {
            PFCTCreateConnection  pfctCreateConnection = (PFCTCreateConnection)::GetProcAddress(m_hModule, "CreateTraceLink_PipeWChar");
            
            if ( pfctCreateConnection )
                m_id = pfctCreateConnection(ModuleName);
        }
    }
    

    /**
     *
     */
    void CTraceViewerConnection_TcpIp_Ansi_Impl::CreateInstance(const char* ModuleName, const char* addr)
    {
        if ( s_pInstance == NULL )
            s_pInstance = new CTraceViewerConnection_TcpIp_Ansi_Impl(ModuleName, addr);
    }
    
    
    /**
     *
     */
    CTraceViewerConnection_TcpIp_Ansi_Impl::CTraceViewerConnection_TcpIp_Ansi_Impl(const char* ModuleName, const char* addr) : CTraceViewerConnection_Impl()
    {
        typedef unsigned int (*PFCTCreateConnection)(const char* szName, const char* addr);
        
        if ( Loaded() )
        {
            PFCTCreateConnection  pfctCreateConnection = (PFCTCreateConnection)::GetProcAddress(m_hModule, "CreateTraceLink_TcpAnsi");
            
            if ( pfctCreateConnection )
                m_id = pfctCreateConnection(ModuleName, addr);
        }
    }

    
    /**
     *
     */
    void CTraceViewerConnection_TcpIp_WChar_Impl::CreateInstance(const char* ModuleName, const char* addr)
    {
        if ( s_pInstance == NULL )
            s_pInstance = new CTraceViewerConnection_TcpIp_WChar_Impl(ModuleName, addr);
    }
    
    
    /**
     *
     */
    CTraceViewerConnection_TcpIp_WChar_Impl::CTraceViewerConnection_TcpIp_WChar_Impl(const char* ModuleName, const char* addr) : CTraceViewerConnection_Impl()
    {
        typedef unsigned int (*PFCTCreateConnection)(const char* szName, const char* addr);
        
        if ( Loaded() )
        {
            PFCTCreateConnection  pfctCreateConnection = (PFCTCreateConnection)::GetProcAddress(m_hModule, "CreateTraceLink_TcpWChar");
            
            if ( pfctCreateConnection )
                m_id = pfctCreateConnection(ModuleName, addr);
        }
    }
}
