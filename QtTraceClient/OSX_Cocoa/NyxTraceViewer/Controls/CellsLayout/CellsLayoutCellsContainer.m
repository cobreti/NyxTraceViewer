//
//  CellsLayoutCellsContainer.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-10.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "CellsLayoutCellsContainer.h"
#import "CellLayoutItem.h"

@implementation CCellsLayoutCellsContainer

- (id)init
{
    [super init];
    
    m_Rect = NSZeroRect;
    m_Items = [[NSMutableArray alloc] initWithCapacity: 0];
    
    return self;
}

- (void)addItem: (CCellsLayout*)item
{
    [m_Items addObject: item];
}

- (void)update: (NSPoint)pt
{
    
}


- (void)drawInView: (NSView*)view withRect: (NSRect)frame
{
    NSInteger       index = 0;
    NSInteger       count = [m_Items count];
    
    while (index < count )
    {
        CCellLayoutItem* item = [m_Items objectAtIndex:index];
        [item drawInView: view withRect:frame];
        
        ++ index;
    }
}


- (void)pick: (NSMutableArray*)items atPoint: (NSPoint)pt
{
    [super pick: items atPoint: pt];
    
    NSInteger       index = 0;
    NSInteger       count  = [m_Items count];
    
    while (index < count)
    {
        [[m_Items objectAtIndex:index] pick:items atPoint: pt];
        ++ index;
    }
}


@end
