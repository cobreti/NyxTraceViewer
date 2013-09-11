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
@class CTracesGroupsView;

@interface CSelectionPanel : NSView
{
    CSelectionPanelBar*     m_Bar;
    CSourcesView*           m_SourcesView;
    CTracesGroupsView*      m_TracesGroupsView;
}

- (BOOL)isFlipped;
- (void)dealloc;

- (IBAction) onPanelSelectionChanged:(id)sender;

@end
