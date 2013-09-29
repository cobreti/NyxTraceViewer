//
//  TraceDataView.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-20.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "TracesDataView.h"

#include "TracesGroup.hpp"
#include "MultiViewTracesIterator.hpp"
#include "TracesGroupListener.h"

@implementation CTracesDataView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {

        m_pTracesGroup = NULL;
        m_pTracesGroupListener = new CTracesGroupListener(self);
        m_pFont = [NSFont fontWithName: @"arial" size:12];
        [m_pFont retain];
        m_LineHeight = [m_pFont ascender] - [m_pFont descender] + 5;
    }
    return self;
}


- (BOOL)isFlipped
{
    return YES;
}


- (void)drawRect:(NSRect)dirtyRect
{
	[super drawRect:dirtyRect];
    
    NSRect  bounds = [self bounds];
    NSRect frame = [self frame];
    NSRect superFrame = [[self superview] frame];

//    [[NSColor blueColor] set];
//    
//    NSBezierPath*       path = [NSBezierPath alloc];
//    
//    NSRect  rc = [self frame];
//    rc.origin = NSZeroPoint;
//    
//    [path appendBezierPathWithOvalInRect: rc];
//    
//    [path stroke];
    
    
    if ( m_pTracesGroup )
    {
        Nyx::UInt32                                     lineNumber = MAX((dirtyRect.origin.y / m_LineHeight) - 1, 0);
        TraceClientCore::CTraceData*                    pTraceData = NULL;
        NSPoint                                         pt = NSMakePoint(10, lineNumber * m_LineHeight);
        NSPoint                                         MaxPt = NSMakePoint(0, pt.y + MAX(dirtyRect.size.height + m_LineHeight*2, m_LineHeight));
//        NSFont*                                         font = [NSFont fontWithName: @"arial" size:12];
        NSDictionary*                                   attributes = [[NSDictionary alloc] initWithObjectsAndKeys: m_pFont, NSFontAttributeName, [NSColor blackColor], NSForegroundColorAttributeName, nil];
        
        m_Pos.MoveToLine(lineNumber);
        
        CViewTracesIterator                             iter(m_Pos);
        
        while (iter.Valid() && pt.y < MaxPt.y)
        {
            pTraceData = iter.TraceData();
            
            NSString*   text = [[NSString alloc] initWithBytes: pTraceData->Data().c_str() length: pTraceData->Data().length()*sizeof(wchar_t) encoding: NSUTF32LittleEndianStringEncoding];
            [text drawAtPoint:pt withAttributes: attributes];
            
            pt.y += m_LineHeight;
            
            ++ iter;
        }
        
        [attributes release];
    }
}


- (void) onTracesGroupChanged: (TraceClientCore::CTracesGroup*)pTracesGroup
{
    if ( m_pTracesGroup != pTracesGroup )
    {
        if ( m_pTracesGroup )
        {
            m_pTracesGroup->Listeners().Remove(m_pTracesGroupListener);
        }
        
        m_pTracesGroup = pTracesGroup;
        
        m_pTracesGroup->Listeners().Add(m_pTracesGroupListener);
        
        [self setNeedsDisplay: YES];
    }
}


- (void) onTracesViewBeginUpdate
{
    
}


- (void) onTracesViewEndUpdate
{
    Nyx::UInt32     linesCount = m_pTracesGroup->LinesCount();
    CGFloat         height = linesCount * m_LineHeight + 15;
    NSRect          frame = [self frame];
    
    
    frame.size.height = height;
    [self setFrame: frame];
    
    if ( linesCount > 0 )
    {
        if ( !m_Pos.Valid() )
            m_Pos = CViewTracesIterator::FirstPos(m_pTracesGroup);
    }

//    [self setNeedsDisplay: YES];
}


@end
