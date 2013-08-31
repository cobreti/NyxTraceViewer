//
//  GroupsView.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-25.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "GroupsView.h"
#import "TracesGroupItemCtrl.h"

@implementation CGroupsView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        
        NSRect  rc = NSMakeRect(10, 10, 100, 20);
        
        TracesGroupItemCtrl* pCtrl = [[TracesGroupItemCtrl alloc] initWithFrame:rc];
        [pCtrl setHidden: NO];
        
        [self addSubView: pCtrl];
        [pCtrl release];
    }
    
    return self;
}

- (void)dealloc
{
    [super dealloc];
}

-(BOOL)isFlipped
{
    return YES;
}

- (void)drawRect:(NSRect)dirtyRect
{
    
//    [[NSColor blueColor] set];
//    NSRect          rc = [self frame];
//    NSBezierPath*   path = [NSBezierPath bezierPath];
//    
//    [path appendBezierPathWithOvalInRect: rc];
//    [path fill];
}

@end
