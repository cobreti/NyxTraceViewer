//
//  AppDelegate.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-15.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "PrefsWindowController.h"
#include <Nyx.hpp>

@interface AppDelegate : NSObject <NSApplicationDelegate> {

    PrefsWindowController*     mPrefsController;
}

@property (assign) IBOutlet NSWindow *window;

- (BOOL)validateToolbarItem:(NSToolbarItem *)theItem;
- (IBAction)onPreferences: (id)sender;

@end
