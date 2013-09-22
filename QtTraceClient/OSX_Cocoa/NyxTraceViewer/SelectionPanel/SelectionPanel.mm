//
//  SelectionPanel.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-07.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "SelectionPanel.h"
#import "SelectionPanelBar.h"
#import "SourcesView/SourcesView.h"
#import "TracesGroupsView/TracesGroupsView.h"

#include "ChannelsListener.h"
#include "TracesGroupMgrListener.h"
#include "TraceClientCoreModule.hpp"
#include "../Controls/TracesGroupsList/TracesGroupInfo.h"


@implementation CSelectionPanel

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self createSelectionBar];
        [self createSourcesView];
        [self createTracesGroupsView];

        m_pChannelsListener = new CChannelsListener(self);
        m_pTracesGroupMgrListener = new CTracesGroupMgrListener(self);
        m_pCurrentGroup = NULL;

        TraceClientCore::CModule&   rModule = TraceClientCore::CModule::Instance();
        
        rModule.ChannelsMgr().AddListener( static_cast<TraceClientCore::IChannelsNotificationsListener*>(m_pChannelsListener) );
        rModule.TracesGroupMgr().Listeners().Add( static_cast<TraceClientCore::ITracesGroupMgrNotificationsListener*>(m_pTracesGroupMgrListener) );
    }
    
    return self;
}

- (BOOL) isFlipped
{
    return YES;
}

- (void) dealloc
{
    [m_Bar release];
    [m_SourcesView release];
    [m_TracesGroupsView release];
    
    [super dealloc];
}


- (void)setSelChangeHandler: (const CActionHandlerInfo&)handler
{
    m_SelChangeHandler = handler;
}


- (IBAction)onPanelSelectionChanged:(id)sender
{
    int panelId = [m_Bar selectedPanel];
    
    switch (panelId)
    {
        case kSelectionPanelBar_SourcesPanel:
            {
                [m_SourcesView setHidden: NO];
                [m_TracesGroupsView setHidden: YES];
            }
            break;
        case kSelectionPanelBar_ChannelsPanel:
            {
                [m_SourcesView setHidden: YES];
                [m_TracesGroupsView setHidden: NO];
            }
            break;
    };
}

- (void)drawRect:(NSRect)dirtyRect
{
    // Drawing code here.
}


- (void)createSelectionBar
{
    
    m_Bar = [[CSelectionPanelBar alloc] initWithFrame: NSMakeRect(0, 0, 200,50)];
    [m_Bar setPanelSelectionChangedHandler: CActionHandlerInfo(@selector(onPanelSelectionChanged:), self)];
    [self addSubview: m_Bar];
    
    [m_Bar calcSize];
    
    m_Bar.translatesAutoresizingMaskIntoConstraints = NO;
    
    [self addConstraint: [NSLayoutConstraint constraintWithItem: m_Bar
                                                      attribute: NSLayoutAttributeTop
                                                      relatedBy: NSLayoutRelationEqual
                                                         toItem: self
                                                      attribute: NSLayoutAttributeTop
                                                     multiplier: 1
                                                       constant: 0 ]];
    
    [self addConstraint: [NSLayoutConstraint constraintWithItem: m_Bar
                                                      attribute: NSLayoutAttributeWidth
                                                      relatedBy: NSLayoutRelationEqual
                                                         toItem: self
                                                      attribute: NSLayoutAttributeWidth
                                                     multiplier: 1
                                                       constant: 10 ]];
}


- (void)createSourcesView
{
    m_SourcesView = [[CSourcesView alloc] initWithFrame: NSMakeRect(0, 50, 200, 400)];
    [self addSubview: m_SourcesView];
    [m_SourcesView setHidden: NO];
    
    m_SourcesView.translatesAutoresizingMaskIntoConstraints = NO;

    [self addConstraint: [NSLayoutConstraint constraintWithItem: m_SourcesView
                                                      attribute: NSLayoutAttributeTop
                                                      relatedBy: NSLayoutRelationEqual
                                                         toItem: m_Bar
                                                      attribute: NSLayoutAttributeBottom
                                                     multiplier: 1
                                                       constant: 0 ]];
    
    [self addConstraint: [NSLayoutConstraint constraintWithItem: m_SourcesView
                                                      attribute: NSLayoutAttributeBottom
                                                      relatedBy: NSLayoutRelationEqual
                                                         toItem: self
                                                      attribute: NSLayoutAttributeBottom
                                                     multiplier: 1
                                                       constant: 0 ]];
    
    [self addConstraint: [NSLayoutConstraint constraintWithItem: m_SourcesView
                                                      attribute: NSLayoutAttributeLeft
                                                      relatedBy: NSLayoutRelationEqual
                                                         toItem: self
                                                      attribute: NSLayoutAttributeLeft
                                                     multiplier: 1
                                                       constant: 0 ]];
    
    [self addConstraint: [NSLayoutConstraint constraintWithItem: m_SourcesView
                                                      attribute: NSLayoutAttributeWidth
                                                      relatedBy: NSLayoutRelationEqual
                                                         toItem: self
                                                      attribute: NSLayoutAttributeWidth
                                                     multiplier: 1
                                                       constant: 0 ]];
}


- (void)createTracesGroupsView
{
    m_TracesGroupsView = [[CTracesGroupsView alloc] initWithFrame: NSMakeRect(0, 50, 200, 400)];
    [self addSubview: m_TracesGroupsView];
    [m_TracesGroupsView setHidden: YES];
    
    m_TracesGroupsView.translatesAutoresizingMaskIntoConstraints = NO;
    
    [self addConstraint: [NSLayoutConstraint constraintWithItem: m_TracesGroupsView
                                                      attribute: NSLayoutAttributeTop
                                                      relatedBy: NSLayoutRelationEqual
                                                         toItem: m_Bar
                                                      attribute: NSLayoutAttributeBottom
                                                     multiplier: 1
                                                       constant: 0 ]];
    
    [self addConstraint: [NSLayoutConstraint constraintWithItem: m_TracesGroupsView
                                                      attribute: NSLayoutAttributeBottom
                                                      relatedBy: NSLayoutRelationEqual
                                                         toItem: self
                                                      attribute: NSLayoutAttributeBottom
                                                     multiplier: 1
                                                       constant: 0 ]];
    
    [self addConstraint: [NSLayoutConstraint constraintWithItem: m_TracesGroupsView
                                                      attribute: NSLayoutAttributeLeft
                                                      relatedBy: NSLayoutRelationEqual
                                                         toItem: self
                                                      attribute: NSLayoutAttributeLeft
                                                     multiplier: 1
                                                       constant: 0 ]];
    
    [self addConstraint: [NSLayoutConstraint constraintWithItem: m_TracesGroupsView
                                                      attribute: NSLayoutAttributeWidth
                                                      relatedBy: NSLayoutRelationEqual
                                                         toItem: self
                                                      attribute: NSLayoutAttributeWidth
                                                     multiplier: 1
                                                       constant: 0 ]];
    
    [m_TracesGroupsView setTracesGroupSelChangeHandler: CActionHandlerInfo(@selector(onTracesGroupSelChanged:), self)];
}


- (void)onNewChannel: (NSDictionary*)params
{
    TraceClientCore::CTraceChannel*     pChannel = (TraceClientCore::CTraceChannel*)[[params objectForKey:@"channel"] pointerValue];
    TraceClientCore::CTracesGroup*      pTracesGroup = NULL;
    
    NYXTRACE(0x0, L"RepositoriesListCtrl - onNewChannel");
    
    [m_SourcesView onNewChannel: params];
    
    pTracesGroup = TraceClientCore::CModule::Instance().TracesGroupMgr().CreateTracesGroup( pChannel->Name() );
    pTracesGroup->AddChannel(pChannel);
    
    [params release];
}


- (void)onNewTracesGroup: (NSDictionary*)params
{
    [m_TracesGroupsView onNewTracesGroup: params];
    
    [params release];
}


- (void)onTracesGroupWillBeDeleted: (NSDictionary*)params
{
    [params release];
}


- (void)onTracesGroupSelChanged: (NSValue*)selection
{
    CTracesGroupInfo*                   pInfo = (CTracesGroupInfo*)[selection pointerValue];
    TraceClientCore::CTracesGroup*      pGroup = pInfo->Group();
    
    m_pCurrentGroup = pInfo;
    
    [m_SourcesView refreshForGroup:m_pCurrentGroup];
    
    [selection release];
    
    if ( m_SelChangeHandler.Valid() )
    {
        NSValue*    groupPtr = [NSValue valueWithPointer: pGroup];
        [groupPtr retain];
        
        [m_SelChangeHandler.Target() performSelector: m_SelChangeHandler.Selector() withObject: groupPtr];
    }
}


@end
