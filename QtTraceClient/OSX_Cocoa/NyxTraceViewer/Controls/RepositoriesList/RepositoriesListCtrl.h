//
//  RepositoriesListCtrl.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-31.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#include "RepositoryInfo.hpp"

@class CVerticalCellsLayout;

class CTracesGroupInfo;

@interface CRepositoriesListCtrl : NSControl
{
    CVerticalCellsLayout*       m_Layout;
    RepositoryInfoList          m_RepositoriesInfo;
}

- (void) addRepositoryInfo: (CRepositoryInfo*) repInfo;
- (void)viewDidEndLiveResize;
- (void)mouseDown:(NSEvent *)theEvent;
- (void)refreshForTracesGroup: (CTracesGroupInfo*)pGroupInfo;

@end
