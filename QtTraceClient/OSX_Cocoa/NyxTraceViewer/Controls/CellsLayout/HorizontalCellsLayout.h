//
//  HorizontalCellsLayout.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-10.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "CellsLayoutCellsContainer.h"

@interface CHorizontalCellsLayout : CCellsLayoutCellsContainer
{
    NSInteger           m_Spacing;
}

- (id)init;
- (void)update: (NSPoint)pt;

@end
