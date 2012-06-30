#include <stdio.h>

#include "TraceLink.hpp"


CTraceLink*		g_pTraceLink = NULL;


int main()
{
    
	return 0;
}


extern "C"
{
    unsigned int CreateTraceLink( const char* szName, int nType );
    void ReleaseTraceLink( const unsigned int& id );
    void WriteTraceA( const unsigned int& id, const char* szData, va_list args );
    void WriteTraceW( const unsigned int& id, const wchar_t* wszData, va_list args );
    void InitModule();
    void TerminateModule();
    
    
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
	unsigned int CreateTraceLink( const char* szName, int nType )
	{
		return g_pTraceLink->CreateTraceLink(szName, nType);
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
