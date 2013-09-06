//
//  RepositoryListCtrlCell.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-31.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

class CRepositoryInfo;

@interface RepositoryListCtrlCell : NSCell
{
    CRepositoryInfo*        m_pInfo;
    NSString*               m_pText;
    NSSize                  m_Size;
    NSImage*                m_UncheckedImg;
    bool                    m_bSelected;
}

- (id)initWithRepositoryInfo: (CRepositoryInfo*) info;
- (void)drawWithFrame: (NSRect)cellFrame inView:(NSView*)view;
- (NSSize)calcDrawInfo: (NSRect)frame;
- (NSSize)cellSize;
- (void)toggleSelected;

@end
