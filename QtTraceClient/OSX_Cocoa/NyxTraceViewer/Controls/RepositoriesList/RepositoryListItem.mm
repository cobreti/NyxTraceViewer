//
//  RepositoryListItem.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-06.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "RepositoryListItem.h"
#include "RepositoryInfo.hpp"

@implementation CRepositoryListItem

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        m_nameCell = [NSCell alloc];
        m_uncheckStateCell = [NSCell alloc];
        m_checkStateCell = [NSCell alloc];
        m_bChecked = false;
    }
    
    return self;
}

- (void)dealloc
{
    [m_checkedImg release];
    [m_UncheckedImg release];
    [m_uncheckStateCell release];
    [m_checkStateCell release];
    [m_nameCell release];
    
    [super dealloc];
}

- (BOOL) isFlipped
{
    return YES;
}

- (void)calcSize
{
//    NSFont*     font = [self font];
//    CGFloat height = [font xHeight];
//    height += [font ascender];
//    height -= [font descender];
//    height += 6;
//    
//    NSDictionary* attributes = [NSDictionary dictionaryWithObjectsAndKeys: [self font], NSFontAttributeName, nil];
//    NSSize string_size = [m_pText sizeWithAttributes:attributes];
//    NSRect frame = [self frame];
    [m_nameCell calcDrawInfo: NSZeroRect];
    [m_uncheckStateCell calcDrawInfo: NSZeroRect];
    
    CGFloat     hMargin = 10;
    CGFloat     vMargin = 5;
    
    NSSize nameSize = [m_nameCell cellSize];
    NSSize checkStateSize = [m_uncheckStateCell cellSize];
    
    m_rcState = NSMakeRect(hMargin,
                           vMargin,
                           checkStateSize.width,
                           checkStateSize.height);
    
    m_rcName = NSMakeRect(m_rcState.origin.x + m_rcState.size.width + hMargin,
                          vMargin + (checkStateSize.height - nameSize.height)/2,
                          nameSize.width,
                          nameSize.height);
    
    [self setFrame: NSMakeRect(0, 0,
                               m_rcState.size.width + m_rcName.size.width + hMargin*3,
                               MAX(m_rcName.size.height, m_rcState.size.height) + vMargin*2)];
}

- (void)setFont: (NSFont*)font
{
    [m_nameCell setFont: font];
}

- (void) setRepositoryInfo: (CRepositoryInfo*) info
{
    NSString* uncheckedImageName = [[NSBundle mainBundle] pathForResource:@"Unchecked-checkbox-icon" ofType:@"png"];
    m_UncheckedImg = [[NSImage alloc] initWithContentsOfFile:uncheckedImageName];
    [m_UncheckedImg setSize: NSMakeSize(16, 16)];

    NSString* checkedImageName = [[NSBundle mainBundle] pathForResource:@"Checked-checkbox-icon" ofType:@"png"];
    m_checkedImg = [[NSImage alloc] initWithContentsOfFile:checkedImageName];
    [m_checkedImg setSize: NSMakeSize(16, 16)];

    m_pInfo = info;
    m_pText = [[NSString alloc] initWithCString: info->Name().c_str() encoding: NSMacOSRomanStringEncoding ];
    [m_nameCell initTextCell: m_pText];
    [m_nameCell setHighlighted: YES];
    [m_nameCell setEditable: YES];
    [m_nameCell setAlignment: NSLeftTextAlignment];
    
    [m_uncheckStateCell initImageCell: m_UncheckedImg];
    [m_checkStateCell initImageCell: m_checkedImg];
}

- (void)drawRect:(NSRect)dirtyRect
{

    [m_nameCell drawWithFrame: m_rcName inView: self];
    
    if (m_bChecked)
        [m_checkStateCell drawWithFrame: m_rcState inView: self];
    else
        [m_uncheckStateCell drawWithFrame: m_rcState inView: self];
    
//    NSRect  cellFrame = [self frame];
//    
//    NSSize imgSize = [m_UncheckedImg size];
//    
//    CGFloat imgY = (cellFrame.size.height - imgSize.height) / 2;
//    NSColor* color = [NSColor blueColor];
//    NSFont* font = [NSFont fontWithName:@"arial" size:12];
//    NSDictionary* attributes = [NSDictionary dictionaryWithObjectsAndKeys: color, NSForegroundColorAttributeName, font, NSFontAttributeName, nil];
//    
//    [m_pText drawInRect:NSMakeRect(cellFrame.origin.x + imgSize.width + 5, 3, cellFrame.size.width - 10, cellFrame.size.height-6) withAttributes:attributes];
//    
//    [m_UncheckedImg drawInRect:NSMakeRect(cellFrame.origin.x, imgY, imgSize.width, imgSize.height) fromRect:NSMakeRect(0, 0, imgSize.width, imgSize.height) operation:NSCompositeSourceOver fraction:1.0];
}

- (void)mouseDown:(NSEvent *)theEvent
{
    NSPoint pt = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    
    if ( NSPointInRect(pt, m_rcState) )
    {
        m_bChecked = !m_bChecked;
        [self setNeedsDisplay: YES];
    }
}

@end
