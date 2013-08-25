//
//  AppDelegate.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-15.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "AppDelegate.h"
#import "TracesWindowController.h"

#include "TraceClientCoreModule.hpp"

@implementation AppDelegate

- (void)dealloc
{    
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    NYXTRACE(0x0, L"application starting");

    TraceClientCore::CTcpTracesReceiversSvr::CSettings       settings;
    
    settings.PortNumber() = 8501;
    settings.UseHandshake() = false;
    TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr(1).Start(settings);

    CTracesWindowController*    pWndController = [[CTracesWindowController alloc] initWithWindowNibName:@"TracesWindow"];
    [pWndController showWindow:self];
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
    NYXTRACE(0x0, L"application terminating");
}

- (BOOL)validateToolbarItem:(NSToolbarItem *)theItem
{
    return YES;
}

@end
