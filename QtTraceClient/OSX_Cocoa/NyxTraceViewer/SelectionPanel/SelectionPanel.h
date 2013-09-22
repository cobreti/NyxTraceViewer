//
//  SelectionPanel.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-07.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#include "../Controls/ActionHandlerInfo.h"

@class CSelectionPanelBar;
@class CSourcesView;
@class CTracesGroupsView;

class CChannelsListener;
class CTracesGroupMgrListener;
class CTracesGroupInfo;

@interface CSelectionPanel : NSView
{
    CSelectionPanelBar*         m_Bar;
    CSourcesView*               m_SourcesView;
    CTracesGroupsView*          m_TracesGroupsView;
    CChannelsListener*          m_pChannelsListener;
    CTracesGroupMgrListener*    m_pTracesGroupMgrListener;
    CTracesGroupInfo*           m_pCurrentGroup;
    
    CActionHandlerInfo          m_SelChangeHandler;
}

- (BOOL)isFlipped;
- (void)dealloc;
- (void)setSelChangeHandler: (const CActionHandlerInfo&)handler;
- (void)onNewChannel: (NSDictionary*)params;
- (void)onNewTracesGroup: (NSDictionary*)params;
- (void)onTracesGroupWillBeDeleted: (NSDictionary*)params;
- (void)onTracesGroupSelChanged: (NSValue*)selection;

@end
