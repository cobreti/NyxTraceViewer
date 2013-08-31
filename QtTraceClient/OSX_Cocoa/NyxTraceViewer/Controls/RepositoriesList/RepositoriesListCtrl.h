//
//  RepositoriesListCtrl.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-31.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "RepositoryListCtrlCell.h"

#include "RepositoryInfo.hpp"

typedef std::list<NSCell*> CellsList;;

@interface CRepositoriesListCtrl : NSControl
{
    RepositoryInfoList          m_RepositoriesInfo;
    CellsList                   m_Cells;
}

- (void) addRepositoryInfo: (CRepositoryInfo*) repInfo;
- (void)viewDidEndLiveResize;
- (void)mouseDown:(NSEvent *)theEvent;

@end
