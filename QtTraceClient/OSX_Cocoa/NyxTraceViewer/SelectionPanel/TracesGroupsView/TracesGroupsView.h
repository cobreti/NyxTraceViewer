//
//  TracesGroupsView.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-08.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#include "ActionHandlerInfo.h"

@class CTracesGroupsListCtrl;

@interface CTracesGroupsView : NSScrollView
{
    CTracesGroupsListCtrl*      m_GroupsListCtrl;
    CActionHandlerInfo          m_TracesGroupSelChangeHandler;
    BOOL                        m_InLiveResize;
}

- (void)setTracesGroupSelChangeHandler: (const CActionHandlerInfo&)handler;

- (void)onNewChannel: (NSDictionary*)params;
- (void)onNewTracesGroup: (NSDictionary*)params;
- (void)onTracesGroupWillBeDeleted: (NSDictionary*)params;

- (IBAction)onTracesGroupSelectionChanged: (id)sender;


@end
