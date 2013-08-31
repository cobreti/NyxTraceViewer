//
//  TracesGroupItemCtrl.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-28.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "TracesGroupItemCtrl.h"
#import "TracesGroupCell.h"

@implementation TracesGroupItemCtrl

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        m_pCell = [[CTracesGroupCell alloc] init];

        [self setCell: m_pCell];
    }
    
    return self;
}

- (void)dealloc
{
    [super dealloc];
}

- (void)drawRect:(NSRect)dirtyRect
{
    NSRect  frame = [self frame];
    
    [m_pCell drawWithFrame:NSMakeRect(0, 0, frame.size.width, frame.size.height) inView:self];
}

@end
