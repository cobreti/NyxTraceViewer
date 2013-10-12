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
#import "settings/TracesDataViewSettings.h"


@implementation CTracesDataView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {

        m_pTracesGroup = NULL;
        m_pTracesGroupListener = new CTracesGroupListener(self);
        m_pSettings = NULL;
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
    
    if ( m_pTracesGroup && m_pSettings )
    {
        Nyx::UInt32                                     lineNumber = MAX((dirtyRect.origin.y / m_pSettings->getLineHeight()) - 1, 0);
        NSPoint                                         pt = NSMakePoint(10, lineNumber * m_pSettings->getLineHeight());
        CTraceLineDisplay*                              LineDisplay = [[CTraceLineDisplay alloc] init];
        
        m_Pos.MoveToLine(lineNumber);
        
        CViewTracesIterator                             iter(m_Pos);
        
        [LineDisplay setTracePos: m_Pos];
        [LineDisplay setDisplayPos: pt];
        [LineDisplay setViewRect: dirtyRect];
        [LineDisplay setSettings: m_pSettings];
        
        [LineDisplay prepareForDrawing];

        while ( [LineDisplay doneDrawing] == NO )
            [LineDisplay drawLine];
        
        [LineDisplay release];
    }

    m_LastVisibleRect = [self visibleRect];
    m_LastFrame = [self frame];
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
    CGFloat         height = linesCount * m_pSettings->getLineHeight() + 15;
    NSRect          frame = [self frame];
    
    frame.size.height = height;
    if ( frame.size.height != m_LastFrame.size.height )
    {
        NSSize  maxLineSize = m_pSettings->getMaxLineSize();
        frame.size.width = maxLineSize.width;
        
        [self setFrame: frame];
    }
    
    if ( (m_LastFrame.origin.y + m_LastFrame.size.height) - (m_LastVisibleRect.origin.y + m_LastVisibleRect.size.height) < 2*m_pSettings->getLineHeight() + 15 )
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


- (void) setSettings: (CTracesDataViewSettings*)pSettings
{
    m_pSettings = pSettings;
}



@end
