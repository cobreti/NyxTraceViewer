//
//  ConnectionSettingsView.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 1/3/2014.
//  Copyright (c) 2014 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "ConnectionSettingsControl.h"

@interface CConnectionSettingsView : NSView
{
    CConnectionSettingsControl*     m_pControl;
    NSMutableArray*                 m_pControls;
}

- (BOOL) isFlipped;
- (void) CreateControls;
- (NSControl*) CreateControl;

@end
