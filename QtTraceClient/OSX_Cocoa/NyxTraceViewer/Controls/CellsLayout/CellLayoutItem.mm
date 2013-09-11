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
    m_Rect.size.width += (m_Margins.left + m_Margins.right);
    m_Rect.size.height += (m_Margins.top + m_Margins.bottom);
}


- (void)drawInView: (NSView*)view
{
    NSRect  cellFrame = m_Rect;
    
    cellFrame.origin.x += m_Margins.left;
    cellFrame.origin.y += m_Margins.top;
    
    [m_Cell drawWithFrame: cellFrame inView:view];
}


@end
