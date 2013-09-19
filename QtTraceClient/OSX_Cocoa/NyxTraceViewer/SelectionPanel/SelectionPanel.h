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

class CChannelsListener;
class CTracesGroupListener;

@interface CSelectionPanel : NSView
{
    CSelectionPanelBar*         m_Bar;
    CSourcesView*               m_SourcesView;
    CTracesGroupsView*          m_TracesGroupsView;
    CChannelsListener*          m_pChannelsListener;
    CTracesGroupListener*       m_pTracesGroupListener;
}

- (BOOL)isFlipped;
- (void)dealloc;
- (void)onNewChannel: (NSDictionary*)params;
- (void)onNewTracesGroup: (NSDictionary*)params;
- (void)onTracesGroupWillBeDeleted: (NSDictionary*)params;
- (void)onTracesGroupSelChanged: (NSValue*)selection;

@end
