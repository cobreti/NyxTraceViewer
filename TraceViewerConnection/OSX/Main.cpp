#include <stdio.h>

#include "TraceLink.hpp"


CTraceLink*		g_pTraceLink = NULL;


int main()
{
    
	return 0;
}


extern "C"
{
    void InitModule();
    void TerminateModule();

    unsigned int CreateTraceLink_PipeAnsi( const char* szName );
    unsigned int CreateTraceLink_PipeWChar( const char* szName );
    unsigned int CreateTraceLink_TcpAnsi( const char* szName, const char* addr );
    unsigned int CreateTraceLink_TcpWChar( const char* szName, const char* addr );
    void ReleaseTraceLink( const unsigned int& id );
    
    void WriteTraceA( const unsigned int& id, const char* szData, va_list args );
    void WriteTraceW( const unsigned int& id, const wchar_t* wszData, va_list args );
    
    
    /**
     *
     */
    void InitModule()
    {
        g_pTraceLink = new CTraceLink();
    }
    
    
    /**
     *
     */
    void TerminateModule()
    {
        delete g_pTraceLink;
        g_pTraceLink = NULL;
    }
    
        
    /**
     *
     */
    unsigned int CreateTraceLink_PipeAnsi(const char* szName)
    {
        return g_pTraceLink->CreateTraceLink_PipeAnsi(szName);
    }
    

    /**
     *
     */
    unsigned int CreateTraceLink_PipeWChar(const char* szName)
    {
        return g_pTraceLink->CreateTraceLink_PipeWChar(szName);
    }
    
    
    /**
     *
     */
    unsigned int CreateTraceLink_TcpAnsi(const char* szName, const char* addr)
    {
        return g_pTraceLink->CreateTraceLink_TcpAnsi(szName, addr);
    }
    
    
    /**
     *
     */
    unsigned int CreateTraceLink_TcpWChar(const char* szName, const char* addr)
    {
        return g_pTraceLink->CreateTraceLink_TcpWChar(szName, addr);
    }
    
    
	/**
	 *
	 */
	void ReleaseTraceLink( const unsigned int& id )
	{
		g_pTraceLink->ReleaseTraceLink(id);
	}


	/**
	 *
	 */
	void WriteTraceA( const unsigned int& id, const char* szData, va_list args )
	{
		g_pTraceLink->WriteTraceA(id, szData, args);
	}


	/**
	 *
	 */
	void WriteTraceW( const unsigned int& id, const wchar_t* wszData, va_list args )
	{
		g_pTraceLink->WriteTraceW(id, wszData, args);
	}

}
