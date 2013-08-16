//
//  AppDelegate.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-15.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "AppDelegate.h"

@implementation AppDelegate

- (void)dealloc
{    
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{    
    NYXTRACE(0x0, L"application starting");
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
    NYXTRACE(0x0, L"application terminating");
}

@end
