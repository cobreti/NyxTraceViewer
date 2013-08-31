//
//  TracesWindowController.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-25.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "TracesWindowController.h"

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

- (void)windowDidLoad
{
    [super windowDidLoad];
    
    // Implement this method to handle any initialization after your window controller's window has been loaded from its nib file.
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

@end
