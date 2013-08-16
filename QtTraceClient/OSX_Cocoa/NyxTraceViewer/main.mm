//
//  main.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-15.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#include <Nyx.hpp>
#import <Cocoa/Cocoa.h>

int main(int argc, char *argv[])
{
    Nyx::CModuleRef             refModule = Nyx::CModule::Alloc();
    Nyx::CTraceCompositorRef    refCompositor = Nyx::CTraceCompositor::Alloc();
    
    refCompositor->SetOutput( Nyx::CConsoleTraceOutput::Alloc() );

    return NSApplicationMain(argc, (const char **)argv);
}
