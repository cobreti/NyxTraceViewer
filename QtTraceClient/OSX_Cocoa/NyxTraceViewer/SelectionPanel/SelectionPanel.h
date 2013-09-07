//
//  SelectionPanel.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-07.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class CSelectionPanelBar;

@interface CSelectionPanel : NSView
{
    CSelectionPanelBar*     m_Bar;
}

- (BOOL)isFlipped;
- (void)dealloc;

@end
