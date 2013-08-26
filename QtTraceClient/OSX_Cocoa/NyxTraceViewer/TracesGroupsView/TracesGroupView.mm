//
//  CTracesGroupView.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-25.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "TracesGroupView.h"
#import "GroupsView.h"


@implementation CTracesGroupView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

-(BOOL)isFlipped
{
    return YES;
}


- (void)drawRect:(NSRect)dirtyRect
{
    // Drawing code here.
 
    [[NSColor redColor] set];
    NSRect          rc = [self frame];
    NSBezierPath*   path = [NSBezierPath bezierPath];
    
    [path appendBezierPathWithOvalInRect: rc];
    [path stroke];
}

- (void)awakeFromNib
{
    NSRect rc = [self frame];
    
    m_SplitView = [[NSSplitView alloc] initWithFrame: rc];
    [self addSubview:m_SplitView];
    
    [self setAutoresizesSubviews: YES];
    
    m_GroupsView = [[CGroupsView alloc] initWithFrame: rc];
    m_RepositoriesView = [[NSView alloc] initWithFrame: rc];
    
    [m_GroupsView setHidden: NO];
    [m_GroupsView setAutoresizingMask: NSViewHeightSizable];

    [m_RepositoriesView setHidden: NO];
    
    [m_SplitView setHidden: NO];
    [m_SplitView setVertical: YES];
    [m_SplitView setAutoresizingMask: NSViewHeightSizable];
    [m_SplitView addSubview: m_GroupsView ];
    [m_SplitView addSubview: m_RepositoriesView ];
}


@end

