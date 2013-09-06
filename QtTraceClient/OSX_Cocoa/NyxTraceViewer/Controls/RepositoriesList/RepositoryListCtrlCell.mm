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
    
    NSString* uncheckedImageName = [[NSBundle mainBundle] pathForResource:@"Unchecked-checkbox-icon" ofType:@"png"];
    
    m_UncheckedImg = [[NSImage alloc] initWithContentsOfFile:uncheckedImageName];
    
//    m_UncheckedImg = [[NSImage alloc] initByReferencingFile:@"Unchecked-checkbox-icon.png"];
    
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

    NSSize imgSize = [m_UncheckedImg size];
    
    CGFloat imgY = (cellFrame.size.height - imgSize.height) / 2;
    NSColor* color = [NSColor blueColor];
    NSFont* font = [NSFont fontWithName:@"arial" size:12];
    NSDictionary* attributes = [NSDictionary dictionaryWithObjectsAndKeys: color, NSForegroundColorAttributeName, font, NSFontAttributeName, nil];

    [m_pText drawInRect:NSMakeRect(cellFrame.origin.x + imgSize.width + 5, cellFrame.origin.y + 3, cellFrame.size.width - 10, cellFrame.size.height-6) withAttributes:attributes];

    [m_UncheckedImg drawInRect:NSMakeRect(cellFrame.origin.x, cellFrame.origin.y + imgY, imgSize.width, imgSize.height) fromRect:NSMakeRect(0, 0, imgSize.width, imgSize.height) operation:NSCompositeSourceOver fraction:1.0];

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
