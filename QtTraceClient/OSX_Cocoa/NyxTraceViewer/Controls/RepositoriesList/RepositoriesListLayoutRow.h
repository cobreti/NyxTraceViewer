//
//  RepositoriesListLayoutRow.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-13.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "HorizontalCellsLayout.h"

class CRepositoryInfo;

@interface CRepositoriesListLayoutRow : CHorizontalCellsLayout
{
    CRepositoryInfo*        m_pInfo;
    NSImage*                m_CheckedImg;
    NSImage*                m_UncheckedImg;
    NSCell*                 m_CheckStateCell;
    BOOL                    m_bChecked;
}

- (id) init: (CRepositoryInfo*)info;
- (BOOL) checked;
- (void) setChecked: (BOOL) checked;
- (CRepositoryInfo*) repositoryInfo;

@end
