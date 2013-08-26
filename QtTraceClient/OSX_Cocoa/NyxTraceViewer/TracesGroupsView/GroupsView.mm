//
//  GroupsView.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-25.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "GroupsView.h"

@implementation CGroupsView

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

    [[NSColor blueColor] set];
    NSRect          rc = [self frame];
    NSBezierPath*   path = [NSBezierPath bezierPath];
    
    [path appendBezierPathWithOvalInRect: rc];
    [path fill];
}

@end
