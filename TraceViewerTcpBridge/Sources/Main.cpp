//
//  Main.cpp
//  TraceViewerTcpBridge
//
//  Created by Danny Thibaudeau on 12-01-02.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <Nyx.hpp>
#include <NyxConsoleTraceOutput.hpp>
#include <NyxNet.hpp>
#include <signal.h>
#include <unistd.h>

#include "TracePipeReceiver.hpp"


Nyx::CEventRef      g_refTerminateEvent;

/**
 *
 */
void AbortHandler(int);
void SigPipeHandler(int);

void AbortHandler(int)
{
//    Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"AbortHandler");
    g_refTerminateEvent->Signal(0);
}

//void SigPipeHandler(int)
//{
//	Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"SigPipe received");
//}


/**
 *
 */
int main( int argc, char *argv[] )
{
    CTracePipeReceiver*                  pReceiver = NULL;
    
    wprintf(L"[%i]\n", getpid());
    
    Nyx::CModuleRef                     refModule = Nyx::CModule::Alloc();
    NyxNet::CModuleRef                  refNetModule = NyxNet::CModule::Alloc();
    
    Nyx::CTraceCompositorRef            refTraceCompositor = Nyx::CTraceCompositor::Alloc();
    refTraceCompositor->SetOutput( Nyx::CConsoleTraceOutput::Alloc() );

    g_refTerminateEvent = Nyx::CEvent::Alloc();
    
    signal(SIGTERM, AbortHandler);
    signal(SIGABRT, AbortHandler);
    signal(SIGINT, AbortHandler);
//    signal(SIGPIPE, SigPipeHandler);
    
    Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"TraceViewerBridge starting");
    
	pReceiver = new CTracePipeReceiver("Test");
	pReceiver->Start();

	g_refTerminateEvent->WaitSignaled();

	pReceiver->Stop();
	delete pReceiver;
    
    Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"TraceViewerBridge ending");
    
    g_refTerminateEvent = NULL;
    
    return 0;
}


