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
    [m_Items insertObject:item atIndex:[m_Items count]];
}

- (void)update: (NSPoint)pt
{
    
}


- (void)drawInView: (NSView*)view
{
    NSInteger       index = 0;
    NSInteger       count = [m_Items count];
    
    while (index < count )
    {
        CCellLayoutItem* item = [m_Items objectAtIndex:index];
        [item drawInView: view];
        
        ++ index;
    }
}



@end
