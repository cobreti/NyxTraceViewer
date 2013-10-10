//
//  TraceDataView.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-20.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "TracesDataView.h"
#import "TraceLineDisplay.h"

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
        
        m_Settings.setFont( [NSFont fontWithName: @"arial" size:12] );
        
        CTracesDataViewSettings::TColumnsOrder      colsOrder;
        
        colsOrder.push_back( CTracesDataViewSettings::eColumn_LineNumber );
        colsOrder.push_back( CTracesDataViewSettings::eColumn_Data );
        m_Settings.setColumnsOrder(colsOrder);
        
        m_Settings.setColumnSettings(CTracesDataViewSettings::eColumn_LineNumber, CColumnSettings());
        m_Settings.setColumnSettings(CTracesDataViewSettings::eColumn_Data, CColumnSettings());
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
    
    if ( m_pTracesGroup )
    {
        Nyx::UInt32                                     lineNumber = MAX((dirtyRect.origin.y / m_LineHeight) - 1, 0);
//        TraceClientCore::CTraceData*                    pTraceData = NULL;
        NSPoint                                         pt = NSMakePoint(10, lineNumber * m_LineHeight);
//        NSPoint                                         MaxPt = NSMakePoint(0, pt.y + MAX(dirtyRect.size.height + m_LineHeight*2, m_LineHeight));
//        NSDictionary*                                   attributes = [[NSDictionary alloc] initWithObjectsAndKeys: m_pFont, NSFontAttributeName, [NSColor blackColor], NSForegroundColorAttributeName, nil];
        CTraceLineDisplay*                              LineDisplay = [[CTraceLineDisplay alloc] init];
        
        m_Pos.MoveToLine(lineNumber);
        
        CViewTracesIterator                             iter(m_Pos);
        
        [LineDisplay setTracePos: m_Pos];
        [LineDisplay setDisplayPos: pt];
        [LineDisplay setViewRect: dirtyRect];
        [LineDisplay setSettings: &m_Settings];
        
        [LineDisplay prepareForDrawing];

        while ( [LineDisplay doneDrawing] == NO )
            [LineDisplay drawLine];
        
        
//        while (iter.Valid() && pt.y < MaxPt.y)
//        {
//            pTraceData = iter.TraceData();
//            
//            NSString*   text = [[NSString alloc] initWithBytes: pTraceData->Data().c_str() length: pTraceData->Data().length()*sizeof(wchar_t) encoding: NSUTF32LittleEndianStringEncoding];
//            [text drawAtPoint:pt withAttributes: attributes];
//            
//            pt.y += m_LineHeight;
//            
//            ++ iter;
//        }
        
//        [attributes release];
        [LineDisplay release];
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
    m_LastVisibleRect = [self visibleRect];
    m_LastFrame = [self frame];
}


- (void) onTracesViewEndUpdate
{
    Nyx::UInt32     linesCount = m_pTracesGroup->LinesCount();
    CGFloat         height = linesCount * m_LineHeight + 15;
    NSRect          frame = [self frame];
    
    frame.size.height = height;
    if ( frame.size.height != m_LastFrame.size.height )
    {
        NSSize  maxLineSize = m_Settings.getMaxLineSize();
        frame.size.width = maxLineSize.width;
        
        [self setFrame: frame];
    }
    
    if ( (m_LastFrame.origin.y + m_LastFrame.size.height) - (m_LastVisibleRect.origin.y + m_LastVisibleRect.size.height) < 2*m_LineHeight + 15 )
    {
        [self scrollRectToVisible: NSMakeRect(m_LastVisibleRect.origin.x, height-1, m_LastVisibleRect.origin.x + m_LastVisibleRect.size.width, height-1)];
        [self setNeedsDisplay: YES];
    }
    
    if ( linesCount > 0 )
    {
        if ( !m_Pos.Valid() )
            m_Pos = CViewTracesIterator::FirstPos(m_pTracesGroup);
    }
}


@end
