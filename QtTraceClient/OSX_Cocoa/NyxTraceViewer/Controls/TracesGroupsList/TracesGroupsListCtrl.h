//
//  TracesGroupsListCtrl.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-08.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#include <list>
#include "ActionHandlerInfo.h"

class CTracesGroupInfo;
@class CVerticalCellsLayout;
@class CTracesGroupLayoutRow;

@interface CTracesGroupsListCtrl : NSControl
{
    CVerticalCellsLayout*   m_Layout;
    CTracesGroupLayoutRow*  m_SelectedRow;
    
    CActionHandlerInfo      m_SelChangeHandler;
}

- (void)calcSize;
- (NSSize)intrinsicContentSize;
- (BOOL)isFlipped;
- (void)addTracesGroup: (CTracesGroupInfo*) info;
- (void)mouseDown:(NSEvent *)theEvent;
- (CTracesGroupInfo*)selection;

- (void)setFrame: (NSRect)framesize;

- (void)setSelChangeHandler:(const CActionHandlerInfo&)handler;

@end
