//
//  TracesGroupLayoutRow.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-10.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "HorizontalCellsLayout.h"

class CTracesGroupInfo;

@interface CTracesGroupLayoutRow : CHorizontalCellsLayout
{
    BOOL                    m_Selected;
    CTracesGroupInfo*       m_GroupInfo;
}

- (id)init;
- (void)setSelected: (BOOL)selected;
- (BOOL)selected;
- (void)drawInView: (NSView*)view withRect: (NSRect)frame;
- (void)setTracesGroupInfo: (CTracesGroupInfo*)info;
- (CTracesGroupInfo*) tracesGroupInfo;

@end
