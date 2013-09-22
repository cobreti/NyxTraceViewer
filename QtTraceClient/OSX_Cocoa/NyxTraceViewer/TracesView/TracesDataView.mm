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
        TraceClientCore::CMultiViewTracesIterator       iter = m_pTracesGroup->FirstPos();
        TraceClientCore::CTraceData*                    pTraceData = NULL;
        NSPoint                                         pt = NSMakePoint(10, 0);
        NSFont*                                         font = [NSFont fontWithName: @"arial" size:12];
        NSDictionary*                                   attributes = [[NSDictionary alloc] initWithObjectsAndKeys: font, NSFontAttributeName, [NSColor blackColor], NSForegroundColorAttributeName, nil];
        
        
        while (iter.Valid())
        {
            pTraceData = iter.TraceData();
            
            NSString*   text = [[NSString alloc] initWithBytes: pTraceData->Data().c_str() length: pTraceData->Data().length()*sizeof(wchar_t) encoding: NSUTF32LittleEndianStringEncoding];
            [text drawAtPoint:pt withAttributes: attributes];
            
            pt.y += 20;
            
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
    CGFloat         height = m_pTracesGroup->LinesCount() * 20;
    NSRect          frame = [self frame];
    
    frame.size.height = height;
    [self setFrame: frame];
    
    [self setNeedsDisplay: YES];
}


@end
