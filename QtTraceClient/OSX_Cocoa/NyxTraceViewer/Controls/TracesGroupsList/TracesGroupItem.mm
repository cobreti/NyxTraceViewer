//
//  TracesGroupItem.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-09.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "TracesGroupItem.h"

#include "TracesGroupInfo.h"

@implementation CTracesGroupItem

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        m_TextField = nullptr;
    }
    
    return self;
}

- (BOOL) isFlipped
{
    return YES;
}

- (void)drawRect:(NSRect)dirtyRect
{
    NSRect  cellFrame = [self frame];
    cellFrame.origin = NSMakePoint(22,5);
    
    [m_NameCell drawWithFrame: cellFrame inView: self];
}


- (void)setTracesGroupInfo: (CTracesGroupInfo*)info
{
    m_pInfo = info;
    
    m_Name = [[NSString alloc] initWithCString: m_pInfo->Name().c_str() encoding:NSMacOSRomanStringEncoding];
    m_NameCell = [[NSCell alloc] initTextCell:m_Name];
}


- (void)mouseDown:(NSEvent *)theEvent
{
    if ( [theEvent clickCount] == 2 )
    {
        NSRect      frame = [self frame];
        frame.origin = NSZeroPoint;
        
        m_TextField = [[NSTextField alloc] initWithFrame:frame];
        [m_TextField setStringValue: m_Name];
        [m_TextField setEditable: YES];
        [m_TextField setDelegate: self];
        [self addSubview: m_TextField];
        
        [[self window] makeFirstResponder: m_TextField];
        [m_TextField lockFocus];
    }
    else
    {
        [[self window] makeFirstResponder: self];
    }
}

- (void)keyDown:(NSEvent *)theEvent
{
    
}


- (void)calcSize
{
    [m_NameCell calcDrawInfo: [self frame]];
    
    NSSize  cellSize = [m_NameCell cellSize];
    
    cellSize.width += 44;
    cellSize.height += 10;
    
    [self setFrameSize: cellSize];
}

- (void)controlTextDidEndEditing:(NSNotification*)aNotification
{
    
    NYXTRACE(0x0, L"control text did end editing");
    
    m_Name = [m_TextField stringValue];
    
    [m_NameCell setStringValue: m_Name];
    
    m_pInfo->Name() = [m_Name cStringUsingEncoding: NSMacOSRomanStringEncoding];
    
    [m_TextField removeFromSuperview];
    [m_TextField release];
    m_TextField = nullptr;
}

@end


