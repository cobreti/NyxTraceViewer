//
//  HorizontalCellsLayout.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-10.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "HorizontalCellsLayout.h"

@implementation CHorizontalCellsLayout

- (id)init
{
    [super init];
    
    m_Spacing = 10;
    
    return self;
}


- (void)update: (NSPoint)pt
{
    NSInteger       index = 0;
    NSInteger       count = [m_Items count];
    NSPoint         p = pt;
    
    m_Rect.origin = pt;
    m_Rect.size = NSZeroSize;
    
    while (index < count)
    {
        CCellsLayout*    item = [m_Items objectAtIndex:index];
        
        [item update: p];
        NSRect itemRect = [item layoutRect];
        
        p.x += itemRect.size.width + m_Spacing;;
        
        m_Rect.size.width += itemRect.size.width + m_Spacing;
        m_Rect.size.height = MAX(m_Rect.size.height, itemRect.size.height);
        
        ++ index;
    }
}

@end
