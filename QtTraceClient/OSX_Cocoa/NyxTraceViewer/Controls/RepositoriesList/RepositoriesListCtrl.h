//
//  RepositoriesListCtrl.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-31.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>
//#import "RepositoryListItem.h"

#include "RepositoryInfo.hpp"

@class CVerticalCellsLayout;

//typedef std::list<CRepositoryListItem*>     RepositoryListItems;

@interface CRepositoriesListCtrl : NSControl
{
    CVerticalCellsLayout*       m_Layout;
    RepositoryInfoList          m_RepositoriesInfo;
//    RepositoryListItems         m_Items;
}

- (void) addRepositoryInfo: (CRepositoryInfo*) repInfo;
- (void)viewDidEndLiveResize;
- (void)mouseDown:(NSEvent *)theEvent;

@end
