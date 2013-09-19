//
//  RepositoriesListLayoutRow.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-13.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "RepositoriesListLayoutRow.h"
#import "../CellsLayout/CellLayoutItem.h"

#include "RepositoryInfo.hpp"

@implementation CRepositoriesListLayoutRow

- (id) init: (CRepositoryInfo*)info;
{
    self = [super init];

    if (self)
    {
        m_pInfo = info;
        
        m_bChecked = NO;

        NSString* uncheckedImageName = [[NSBundle mainBundle] pathForResource:@"Unchecked-checkbox-icon" ofType:@"png"];
        m_UncheckedImg = [[NSImage alloc] initWithContentsOfFile:uncheckedImageName];
        [m_UncheckedImg setSize: NSMakeSize(16, 16)];
        
        NSString* checkedImageName = [[NSBundle mainBundle] pathForResource:@"Checked-checkbox-icon" ofType:@"png"];
        m_CheckedImg = [[NSImage alloc] initWithContentsOfFile:checkedImageName];
        [m_CheckedImg setSize: NSMakeSize(16, 16)];

        NSString*  text = [[NSString alloc] initWithCString: info->Name().c_str() encoding: NSMacOSRomanStringEncoding ];
        
        m_CheckStateCell = [[NSCell alloc] initImageCell: m_UncheckedImg];
        
        CCellLayoutItem* item = [[CCellLayoutItem alloc] initWithCell: m_CheckStateCell ];
        [item setMargins: MakeLayoutMargins(10, 0, 10, 0)];
        [self addItem: item];
        
        item = [[CCellLayoutItem alloc] initWithCell: [[NSCell alloc] initTextCell: text]];
        [item setMargins: MakeLayoutMargins(10, 0, 10, 0)];
        [self addItem: item];
        
        [self setMargins: MakeLayoutMargins(0, 5, 0, 5)];
    }
    
    return self;
}

- (BOOL) checked
{
    return m_bChecked;
}


- (void) setChecked: (BOOL) checked
{
    m_bChecked = checked;
    
    if ( m_bChecked )
    {
        [m_CheckStateCell setImage: m_CheckedImg];
    }
    else
    {
        [m_CheckStateCell setImage: m_UncheckedImg];
    }
}

- (CRepositoryInfo*) repositoryInfo
{
    return m_pInfo;
}


@end
