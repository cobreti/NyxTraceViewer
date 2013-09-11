//
//  CellsLayoutCellsContainer.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-10.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "CellsLayout.h"

@interface CCellsLayoutCellsContainer : CCellsLayout
{
    NSMutableArray*     m_Items;
}

- (id)init;
- (void)addItem: (CCellsLayout*)item;
- (void)update: (NSPoint)pt;
- (void)drawInView: (NSView*)view;

@end
