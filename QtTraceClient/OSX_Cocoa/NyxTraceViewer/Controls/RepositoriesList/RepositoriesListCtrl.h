//
//  RepositoriesListCtrl.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-31.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "RepositoryListItem.h"

#include "RepositoryInfo.hpp"

typedef std::list<CRepositoryListItem*>     RepositoryListItems;

@interface CRepositoriesListCtrl : NSControl
{
    RepositoryInfoList          m_RepositoriesInfo;
    RepositoryListItems         m_Items;
}

- (void) addRepositoryInfo: (CRepositoryInfo*) repInfo;
- (void)viewDidEndLiveResize;

@end
