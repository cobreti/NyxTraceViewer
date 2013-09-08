//
//  SelectionPanel.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-07.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class CSelectionPanelBar;
@class CSourcesView;

@interface CSelectionPanel : NSView
{
    CSelectionPanelBar*     m_Bar;
    CSourcesView*           m_SourcesView;
}

- (BOOL)isFlipped;
- (void)dealloc;

- (IBAction) onPanelSelectionChanged:(id)sender;

@end
