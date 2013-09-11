//
//  CellsLayout.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-10.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "CellsLayout.h"
#import "CellLayoutItem.h"

@implementation CCellsLayout

- (id)init
{
    [super init];
    
    m_Rect = NSZeroRect;
    m_Margins = MakeLayoutMargins(0, 0, 0, 0);
    
    return self;
}

- (void)addItem: (CCellsLayout*)item;
{
}

- (void)update: (NSPoint)pt
{
    
}


- (void)drawInView: (NSView*)view withRect: (NSRect)frame
{
}


- (NSRect)layoutRect
{
    return m_Rect;
}

- (void)setMargins: (SCellsLayoutMargins)margins
{
    m_Margins = margins;
}


- (SCellsLayoutMargins)margins
{
    return m_Margins;
}

- (void)pick: (NSMutableArray*)items atPoint: (NSPoint)pt
{
    if ( NSPointInRect(pt, m_Rect) )
    {
        [items addObject: self];
    }
}


@end
