//
//  TracesGroupsListCtrl.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-08.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#include <list>

class CTracesGroupInfo;
@class CVerticalCellsLayout;

@interface CTracesGroupsListCtrl : NSControl
{
    CVerticalCellsLayout*   m_Layout;
}

- (void)calcSize;
- (NSSize)intrinsicContentSize;
- (BOOL)isFlipped;
- (void)addTracesGroup: (CTracesGroupInfo*) info;

@end
