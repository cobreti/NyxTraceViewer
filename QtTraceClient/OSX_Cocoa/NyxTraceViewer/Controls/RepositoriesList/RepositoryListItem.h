//
//  RepositoryListItem.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-06.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

class CRepositoryInfo;

@interface CRepositoryListItem : NSControl
{
    CRepositoryInfo*        m_pInfo;
    NSString*               m_pText;
    NSSize                  m_Size;
    NSImage*                m_UncheckedImg;
    NSImage*                m_checkedImg;
    bool                    m_bSelected;
    NSCell*                 m_nameCell;
    NSCell*                 m_uncheckStateCell;
    NSCell*                 m_checkStateCell;
    NSRect                  m_rcState;
    NSRect                  m_rcName;
    bool                    m_bChecked;
}

- (void)dealloc;
- (void)setRepositoryInfo: (CRepositoryInfo*) info;
- (void)calcSize;
- (void)setFont: (NSFont*)font;
- (void)mouseDown:(NSEvent *)theEvent;

@end
