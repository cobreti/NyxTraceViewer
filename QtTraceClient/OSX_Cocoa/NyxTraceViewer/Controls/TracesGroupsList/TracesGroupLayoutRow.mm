//
//  TracesGroupLayoutRow.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-10.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "TracesGroupLayoutRow.h"

@implementation CTracesGroupLayoutRow

- (id) init
{
    [super init];

    m_Selected = NO;
    m_GroupInfo = NULL;
    
    return self;
}

- (void)setSelected: (BOOL)selected
{
    m_Selected = selected;
}


- (BOOL)selected
{
    return m_Selected;
}


- (void)drawInView: (NSView*)view withRect: (NSRect)frame
{
    if ( m_Selected )
    {
        [[NSColor controlHighlightColor] set];
        
        NSBezierPath*       path = [NSBezierPath alloc];
        NSRect              rc = m_Rect;
        
        rc.size.width = frame.size.width;
        
        [path appendBezierPathWithRect: rc];
        [path fill];
    }
    
    [super drawInView: view withRect: frame];
}


- (void)setTracesGroupInfo: (CTracesGroupInfo*)info
{
    m_GroupInfo = info;
}


- (CTracesGroupInfo*) tracesGroupInfo
{
    return m_GroupInfo;
}


@end
