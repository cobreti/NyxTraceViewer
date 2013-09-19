//
//  TracesGroupsView.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-08.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "TracesGroupsView.h"
#import "../../Controls/TracesGroupsList/TracesGroupsListCtrl.h"

#include "../../Controls/TracesGroupsList/TracesGroupInfo.h"
#include "TraceClientCoreModule.hpp"


@implementation CTracesGroupsView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self setHasHorizontalScroller: YES];
        [self setHasVerticalScroller: YES];
        
        [self createTracesGroupsListCtrl];
    }
    
    return self;
}

- (BOOL)isFlipped
{
    return YES;
}

- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect: dirtyRect];
}

- (void)createTracesGroupsListCtrl
{
    m_GroupsListCtrl = [[CTracesGroupsListCtrl alloc] initWithFrame: [self frame]];
    [self setDocumentView: m_GroupsListCtrl];
    [m_GroupsListCtrl calcSize];
    
    m_GroupsListCtrl.translatesAutoresizingMaskIntoConstraints = NO;

    [self addConstraint: [NSLayoutConstraint constraintWithItem: m_GroupsListCtrl
                                                      attribute: NSLayoutAttributeWidth
                                                      relatedBy: NSLayoutRelationGreaterThanOrEqual
                                                         toItem: self
                                                      attribute: NSLayoutAttributeWidth
                                                     multiplier: 1
                                                       constant: 0 ]];
}


- (void)onNewChannel: (NSDictionary*)params
{
    TraceClientCore::CTraceChannel* pChannel = (TraceClientCore::CTraceChannel*)[[params objectForKey:@"channel"] pointerValue];
    
    NYXTRACE(0x0, L"RepositoriesListCtrl - onNewChannel");
}


- (void)onNewTracesGroup: (NSDictionary*)params
{
    TraceClientCore::CTracesGroup*  pGroup = (TraceClientCore::CTracesGroup*)[[params objectForKey:@"tracesgroup"] pointerValue];

    CTracesGroupInfo*   pInfo = new CTracesGroupInfo();
    pInfo->Name() = pGroup->Name();
    [m_GroupsListCtrl addTracesGroup: pInfo];
    [m_GroupsListCtrl calcSize];
    [m_GroupsListCtrl setNeedsDisplay: YES];
}


- (void)onTracesGroupWillBeDeleted: (NSDictionary*)params
{
    
}

@end
