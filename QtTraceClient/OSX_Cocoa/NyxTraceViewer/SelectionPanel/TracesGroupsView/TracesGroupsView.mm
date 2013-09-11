//
//  TracesGroupsView.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-08.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "TracesGroupsView.h"
#import "../../Controls/TracesGroupsList/TracesGroupsListCtrl.h"

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

@end
