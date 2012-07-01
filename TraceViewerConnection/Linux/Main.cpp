#include <stdio.h>

#include "TraceLink.hpp"


CTraceLink*		g_pTraceLink = NULL;


static void Init() __attribute__((__constructor__));
static void Init()
{
	g_pTraceLink = new CTraceLink();
}

static void Uninit() __attribute__((__destructor__));
static void Uninit()
{
	delete g_pTraceLink;
}

int main()
{
	return 0;
}


extern "C"
{
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
