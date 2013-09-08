//
//  CTracesGroupView.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-25.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "TracesGroupView.h"
#import "../Controls/RepositoriesList/RepositoriesListCtrl.h"

#include <Nyx.hpp>


@implementation CTracesGroupView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {

        [self setHasHorizontalScroller: YES];
        [self setHasVerticalScroller: YES];
        
        mCtrl = [[CRepositoriesListCtrl alloc] initWithFrame: [self frame]];
        [mCtrl setAutoresizingMask: NSViewHeightSizable | NSViewWidthSizable];
        [self setDocumentView: mCtrl];
        [mCtrl calcSize];
        
    }
    
    return self;
}

-(BOOL)isFlipped
{
    return YES;
}


- (void)dealloc
{
//    [m_SplitView release];
//    [m_GroupsView release];
//    [m_RepositoriesView release];
    
    [mCtrl release];
    
    NYXTRACE(0x0, L"TracesGroupView dealloc");
    [super dealloc];
}

- (void)drawRect:(NSRect)dirtyRect
{
//    [[NSColor redColor] set];
//    NSRect          rc = [self frame];
//    NSBezierPath*   path = [NSBezierPath bezierPath];
//    
//    [path appendBezierPathWithOvalInRect: rc];
//    [path stroke];

    [[NSColor whiteColor] set];
    
    NSBezierPath*   path = [NSBezierPath bezierPath];
    [path setLineWidth: 1];
    [path appendBezierPathWithRect: [self frame]];
    [path fill];
}

- (void)awakeFromNib
{
    NSRect rc = [self frame];
    
    [self setHasHorizontalScroller: YES];
    [self setHasVerticalScroller: YES];
    
    mCtrl = [[CRepositoriesListCtrl alloc] initWithFrame: [self frame]];
    [mCtrl setAutoresizingMask: NSViewHeightSizable | NSViewWidthSizable];
    [self setDocumentView: mCtrl];
    [mCtrl calcSize];
    
//    m_SplitView = [[NSSplitView alloc] initWithFrame: rc];
//    [self addSubview:m_SplitView];
//    
//    [self setAutoresizesSubviews: YES];
//    
//    m_GroupsView = [[CGroupsView alloc] initWithFrame: rc];
//    m_RepositoriesView = [[NSView alloc] initWithFrame: rc];
//    
//    [m_GroupsView setHidden: NO];
//    [m_GroupsView setAutoresizingMask: NSViewHeightSizable];
//
//    [m_RepositoriesView setHidden: NO];
//    
//    [m_SplitView setHidden: NO];
//    [m_SplitView setVertical: YES];
//    [m_SplitView setAutoresizingMask: NSViewHeightSizable];
//    [m_SplitView addSubview: m_GroupsView ];
//    [m_SplitView addSubview: m_RepositoriesView ];
}


@end

