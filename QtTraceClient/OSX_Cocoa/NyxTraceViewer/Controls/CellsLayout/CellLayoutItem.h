//
//  CellLayoutData.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-10.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "CellsLayout.h"

@interface CCellLayoutItem : CCellsLayout
{
    NSCell*         m_Cell;
}

- (id)initWithCell: (NSCell*)cell;
- (void)update: (NSPoint)pt;
- (void)drawInView: (NSView*)view;

@end
