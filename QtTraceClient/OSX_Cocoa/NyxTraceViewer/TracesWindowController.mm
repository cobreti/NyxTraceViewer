//
//  TracesWindowController.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-25.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "TracesWindowController.h"

#include "TraceClientCoreModule.hpp"

@interface CTracesWindowController ()

@end

@implementation CTracesWindowController

- (id)initWithWindow:(NSWindow *)window
{
    self = [super initWithWindow:window];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (id)initWithWindowNibName:(NSString *)windowNibName
{
    self = [super initWithWindowNibName:windowNibName];
    if (self)
    {
        NSString* channelsHidden = [[NSBundle mainBundle] pathForResource:@"channels_hidden" ofType:@"png"];
        m_channelsHidden = [[NSImage alloc] initWithContentsOfFile:channelsHidden];

        NSString* channelsVisible = [[NSBundle mainBundle] pathForResource:@"channels_visible" ofType:@"png"];
        m_channelsVisible = [[NSImage alloc] initWithContentsOfFile:channelsVisible];
        
    }
    
    return self;
}

- (void)windowDidLoad
{
    [super windowDidLoad];

    [[self selectionPanel] setSelChangeHandler: CActionHandlerInfo( @selector(onTracesGroupSelectionChanged:), self)];
}

- (void)windowWillClose:(NSNotification *)notification
{
    [self release];
}


- (void)dealloc
{
    [super dealloc];
}

- (IBAction)onChannelsShowHide:(id)sender
{
    NSToolbarItem*  pItem = (NSToolbarItem*)sender;

    NSView* pLeftView = [[self.m_SplitView subviews] objectAtIndex:0];
    NSView* pRightView = [[self.m_SplitView subviews] objectAtIndex:1];
    BOOL bCollapsed = [self.m_SplitView isSubviewCollapsed:pLeftView];
    
    NSRect leftFrame;
    NSRect rightFrame = [pRightView frame];
    NSRect overallFrame = [self.m_SplitView frame];
    
    CGFloat dividerThickness = [self.m_SplitView dividerThickness];
    
    if ( bCollapsed )
    {
        leftFrame = rightFrame;

        leftFrame.origin.x = 0;
        leftFrame.size.width = m_LastChannelsPanelWidth;
        
        [pLeftView setHidden: NO];
        [pLeftView setFrame:leftFrame];

        rightFrame.origin.x = leftFrame.size.width + dividerThickness;
        rightFrame.size.width = overallFrame.size.width - rightFrame.origin.x;
        [pRightView setFrame:rightFrame];
        
        [pRightView display];
        [pLeftView display];
        [self.m_SplitView display];
        
        [pItem setImage: m_channelsVisible];
    }
    else
    {
        leftFrame = [pLeftView frame];
        m_LastChannelsPanelWidth = leftFrame.size.width;
        
        [pLeftView setHidden: YES];
        rightFrame.size.width = overallFrame.size.width;
        rightFrame.origin.x = 0;
//        [pRightView setFrameSize:NSMakeSize(overallFrame.size.width, overallFrame.size.height)];
        [pRightView setFrame:rightFrame];
        [pRightView display];
        [self.m_SplitView display];
        
        [pItem setImage: m_channelsHidden];
    }
}

- (BOOL)validateToolbarItem:(NSToolbarItem *)theItem
{
    return YES;
}

- (NSArray*)toolbarAllowedItemIdentifiers:(NSToolbar*)toolbar
{
    return NULL;
}


- (void)onTracesGroupSelectionChanged:(NSValue*)tracesGroupPtr
{
    TraceClientCore::CTracesGroup*      pGroup = (TraceClientCore::CTracesGroup*)[tracesGroupPtr pointerValue];
    
    [[self contentView] onTracesGroupChanged: pGroup];
    
    [tracesGroupPtr release];
}


@end
