// TraceClientLink.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "TraceClientLinkDLL.h"
#include "TraceLink.hpp"

#include <NyxNet.hpp>

CTraceLink*                             g_pTraceLink = NULL;
NyxNet::CModuleRef                      g_refNetModule;


void OnProcessAttach();
void OnProcessDetach();


#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			OnProcessAttach();
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			OnProcessDetach();
			break;
	}
    return TRUE;
}



/**
 *
 */
void OnProcessAttach()
{
    g_pTraceLink = new CTraceLink();
    g_refNetModule = NyxNet::CModule::Alloc();
}


/**
 *
 */
void OnProcessDetach()
{
    delete g_pTraceLink;
    g_pTraceLink = NULL;

    g_refNetModule = NULL;
}



#ifdef _MANAGED
#pragma managed(pop)
#endif


/**
 *
 */
unsigned int __cdecl CreateTraceLink_PipeAnsi( const char* szName )
{
    return g_pTraceLink->CreateTraceLink_PipeAnsi(szName);
}


/**
 *
 */
unsigned int __cdecl CreateTraceLink_PipeWChar( const char* szName )
{
    return g_pTraceLink->CreateTraceLink_PipeWChar(szName);
}


/**
 *
 */
unsigned int __cdecl CreateTraceLink_TcpAnsi( const char* szName, const char* szAddr )
{
    return g_pTraceLink->CreateTraceLink_TcpAnsi(szName, szAddr);
}


/**
 *
 */
unsigned int __cdecl CreateTraceLink_TcpWChar( const char* szName, const char* szAddr )
{
    return g_pTraceLink->CreateTraceLink_TcpWChar(szName, szAddr);
}


/**
 *
 */
void __cdecl ReleaseTraceLink( const unsigned int& id )
{
    g_pTraceLink->ReleaseTraceLink(id);
}


/**
 *
 */
void __cdecl WriteTraceA( const unsigned int& id, const char* szData, va_list args )
{
    g_pTraceLink->WriteTraceA(id, szData, args);
}


/**
 *
 */
void __cdecl WriteTraceW( const unsigned int& id, const wchar_t* wszData, va_list args )
{
    g_pTraceLink->WriteTraceW(id, wszData, args);
}
