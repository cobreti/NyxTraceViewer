//
//  AppDelegate.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-15.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "AppDelegate.h"

#include "TraceClientCoreModule.hpp"

@implementation AppDelegate

- (void)dealloc
{    
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    TraceClientCore::CTcpTracesReceiversSvr::CSettings       settings;
    
    settings.PortNumber() = 8501;
    settings.UseHandshake() = false;
    TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr(1).Start(settings);

    NYXTRACE(0x0, L"application starting");
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
    NYXTRACE(0x0, L"application terminating");
}

@end
