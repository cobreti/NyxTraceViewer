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
    
    return self;
}

- (void)addItem: (CCellsLayout*)item;
{
}

- (void)update: (NSPoint)pt
{
    
}


- (void)drawInView: (NSView*)view
{
}


- (NSRect)layoutRect
{
    return m_Rect;
}


@end
