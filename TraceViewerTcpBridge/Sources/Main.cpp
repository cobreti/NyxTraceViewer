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

#include "Application.hpp"


/**
 *
 */
int main( int argc, char *argv[] )
{
    Nyx::CModuleRef                     refModule = Nyx::CModule::Alloc();
    NyxNet::CModuleRef                  refNetModule = NyxNet::CModule::Alloc();
    
    Nyx::CTraceCompositorRef            refTraceCompositor = Nyx::CTraceCompositor::Alloc();
    refTraceCompositor->SetOutput( Nyx::CConsoleTraceOutput::Alloc() );

    CApplication		App;

    App.Init();

    App.Run();

    App.Terminate();

    
    return 0;
}


