//
//  CellLayoutData.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-10.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "CellLayoutItem.h"

@implementation CCellLayoutItem

- (id)initWithCell: (NSCell*)cell
{
    [super init];
    
    m_Cell = cell;
    
    return self;
}


- (void)update: (NSPoint)pt
{
    [m_Cell calcDrawInfo: NSZeroRect];
    
    m_Rect.origin = pt;
    m_Rect.size = [m_Cell cellSize];
}


- (void)drawInView: (NSView*)view
{
    [m_Cell drawWithFrame: m_Rect inView:view];
}


@end
