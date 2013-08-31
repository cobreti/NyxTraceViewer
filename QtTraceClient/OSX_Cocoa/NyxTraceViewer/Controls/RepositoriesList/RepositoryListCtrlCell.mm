//
//  RepositoryListCtrlCell.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-31.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "RepositoryListCtrlCell.h"

#include "RepositoryInfo.hpp"


@implementation RepositoryListCtrlCell

- (id) initWithRepositoryInfo: (CRepositoryInfo*) info
{
    m_pInfo = info;
    m_pText = [[NSString alloc] initWithCString: info->Name().c_str() encoding: NSMacOSRomanStringEncoding ];
    return self;
}

- (void)drawWithFrame: (NSRect)cellFrame inView:(NSView*)view
{
    if (m_bSelected)
    {
        [[NSColor lightGrayColor] set];
        NSBezierPath*   path = [NSBezierPath bezierPath];
        [path setLineWidth: 5];
        [path appendBezierPathWithRect: cellFrame];
        [path fill];
    }

    NSColor* color = [NSColor blueColor];
    NSFont* font = [NSFont fontWithName:@"arial" size:12];
    NSDictionary* attributes = [NSDictionary dictionaryWithObjectsAndKeys: color, NSForegroundColorAttributeName, font, NSFontAttributeName, nil];

    [m_pText drawInRect:NSMakeRect(cellFrame.origin.x + 5, cellFrame.origin.y + 3, cellFrame.size.width - 10, cellFrame.size.height-6) withAttributes:attributes];
    

}

- (NSSize)calcDrawInfo: (NSRect)frame
{
    NSFont*     font = [self font];
    CGFloat height = [font xHeight];
    height += [font ascender];
    height -= [font descender];
    height += 6;

    NSDictionary* attributes = [NSDictionary dictionaryWithObjectsAndKeys: [self font], NSFontAttributeName, nil];
    NSSize string_size = [m_pText sizeWithAttributes:attributes];
    
    m_Size = NSMakeSize(string_size.width, height);
    return m_Size;
}

- (NSSize)cellSize
{
    return m_Size;
}

- (void)toggleSelected
{
    m_bSelected = !m_bSelected;
}

@end
