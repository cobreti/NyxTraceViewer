// TraceClientLink.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <mmsystem.h>
#include "Nyx.hpp"
#include "NyxNet.hpp"
#include "NyxNetPipeTraceOutput.hpp"
#include "TraceClientLinkDLL.h"

#include <map>

typedef		std::map<unsigned int, Nyx::CTraceCompositorRef>			TraceCompositorsMap;


enum
{
    kBufferSize = 8192
};

Nyx::CMutexRef                          g_refMutex;
Nyx::CModuleRef							g_refModule;
Nyx::CTraceCompositorRef				g_refTraceCompositor;
TraceCompositorsMap						g_TraceCompositorsTable;
unsigned int							g_NextAvailID = 0x0001;
char                                    g_AnsiBuffer[kBufferSize];
wchar_t                                 g_WCharBuffer[kBufferSize];



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
	g_refModule = Nyx::CModule::Alloc();
    g_refMutex = Nyx::CMutex::Alloc();
	g_refTraceCompositor = Nyx::CTraceCompositor::Alloc(Nyx::eTCCS_Ansi, false);
	g_refTraceCompositor->SetOutput( NyxNet::CPipeTraceOutput::Alloc("TraceClientLink") );

	//Nyx::CTraceStream(0x0).Write("OnProcessAttach");
}


/**
 *
 */
void OnProcessDetach()
{
	//Nyx::CTraceStream(0x0).Write("OnProcessDetach");
    g_refMutex = NULL;
	g_refModule = NULL;
	g_refTraceCompositor = NULL;
}



#ifdef _MANAGED
#pragma managed(pop)
#endif


/**
 *
 */
unsigned int __cdecl CreateTraceLink( const char* szName, int nType )
{
    Nyx::ETraceCompositorCharSet    eCharSet = Nyx::eTCCS_Ansi;
	Nyx::CTraceCompositorRef		refTraceCompositor;
	unsigned int					id = g_NextAvailID ++;

    if ( nType != 0 )
        eCharSet = Nyx::eTCCS_WideChar;

    refTraceCompositor = Nyx::CTraceCompositor::Alloc(eCharSet, false);

	g_TraceCompositorsTable.insert( std::make_pair(id, refTraceCompositor) );
	
	refTraceCompositor->SetOutput( NyxNet::CPipeTraceOutput::Alloc(szName) );

	return id;
}


/**
 *
 */
void __cdecl ReleaseTraceLink( const unsigned int& id )
{
	TraceCompositorsMap::iterator		pos = g_TraceCompositorsTable.find(id);

	g_TraceCompositorsTable.erase(pos);
}


/**
 *
 */
void __cdecl WriteTraceA( const unsigned int& id, const char* szData, va_list args )
{
    Nyx::TLock<Nyx::CMutex>     Lock(g_refMutex, true);

	TraceCompositorsMap::iterator		pos = g_TraceCompositorsTable.find(id);

	if ( pos != g_TraceCompositorsTable.end() )
	{
		Nyx::CTraceCompositorRef	refTraceCompositor = pos->second;
		Nyx::CTraceStream			stream(0xFF, refTraceCompositor);

        vsprintf(g_AnsiBuffer, szData, args);

		stream.Write(g_AnsiBuffer);
	}
}


/**
 *
 */
void __cdecl WriteTraceW( const unsigned int& id, const wchar_t* wszData, va_list args )
{
    Nyx::TLock<Nyx::CMutex>     Lock(g_refMutex, true);

	TraceCompositorsMap::iterator		pos = g_TraceCompositorsTable.find(id);

	if ( pos != g_TraceCompositorsTable.end() )
	{
		Nyx::CTraceCompositorRef	refTraceCompositor = pos->second;
		Nyx::CTraceStream			stream(0xFF, refTraceCompositor);

        wvsprintf(g_WCharBuffer, wszData, args);

		stream.Write(g_WCharBuffer);
	}
}
