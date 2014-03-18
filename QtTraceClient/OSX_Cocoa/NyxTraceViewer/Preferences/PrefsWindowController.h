//
//  PrefsControllerWindowController.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-10-19.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "ConnectionSettings/ConnectionSettingsView.h"

@interface PrefsWindowController : NSWindowController
{   
    CConnectionSettingsView*        m_pConnectionSettingsView;
    NSScrollView*                   m_pScrollView;
}

- (void) CreateConnectionSettingsView;

@property (assign) IBOutlet NSWindow* prefsWindow;


@end
