//
//  TraceLineDisplay.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-10-07.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "TraceLineDisplay.h"
#import "settings/TracesDataViewSettings.h"


@implementation CTraceLineDisplay

- (id)init
{
    self = [super init];
    
    if (self)
    {
        m_pSettings = NULL;
        m_DisplayPos = NSZeroPoint;
        m_MaxPos = NSZeroPoint;
        m_ViewRect = NSZeroRect;
        m_TextAttributes = NULL;
    }
    
    return self;
}


- (void)dealloc
{
    if (m_TextAttributes)
        [m_TextAttributes dealloc];
    
    [super dealloc];
}


- (void)setTracePos: (const CViewTracesIterator&)TracePos
{
    m_TracePos = TracePos;
}


- (const CViewTracesIterator&) getTracePos
{
    return m_TracePos;
}


- (void)setDisplayPos: (NSPoint) DisplayPos
{
    m_DisplayPos = DisplayPos;
}


- (NSPoint)getDisplayPos
{
    return m_DisplayPos;
}


- (void)setViewRect: (NSRect)ViewRect
{
    m_ViewRect = ViewRect;
}


- (NSRect)getViewRect
{
    return m_ViewRect;
}

- (void)setSettings: (CTracesDataViewSettings*) pSettings
{
    m_pSettings = pSettings;
}


- (void)prepareForDrawing
{
    if ( m_TextAttributes )
        [m_TextAttributes release];
    
    m_MaxPos = NSMakePoint(0, m_DisplayPos.y + MAX(m_ViewRect.size.height + m_pSettings->getLineHeight()*2, m_pSettings->getLineHeight() ));
    m_TextAttributes = [[NSDictionary alloc] initWithObjectsAndKeys: m_pSettings->getFont(), NSFontAttributeName, [NSColor blackColor], NSForegroundColorAttributeName, nil];
}


- (BOOL)doneDrawing
{
    if ( !m_TracePos.Valid() || m_DisplayPos.y > m_MaxPos.y )
        return YES;
    
    return NO;
}

- (void)drawLine
{
    TraceClientCore::CTraceData*                    pTraceData = m_TracePos.TraceData();
    
    m_DisplayPos.x = 0;
    
    [self drawLineNumber: pTraceData];
    [self drawTraceData: pTraceData];
    
    m_DisplayPos.y += m_pSettings->getLineHeight();
    
    ++ m_TracePos;
}


- (void)drawLineNumber: (TraceClientCore::CTraceData*) pTraceData
{
    Nyx::UInt32         LineNumber = m_TracePos.getLineNumber() + 1;
    NSString*           text = [NSString stringWithFormat: @"%d", LineNumber ];
    CGSize              size = [text sizeWithAttributes: m_TextAttributes];
    CColumnSettings&    settings = m_pSettings->rgetColumnSettings( CTracesDataViewSettings::eColumn_LineNumber );
    NSSize              colMaxSize = settings.getMaxSize();
    
    m_DisplayPos.x += settings.getMargins().left;
    
    colMaxSize.width = MAX(colMaxSize.width, size.width);
    colMaxSize.height = MAX(colMaxSize.height, size.height);
    
    settings.setMaxSize(colMaxSize);
    
    [text drawAtPoint:m_DisplayPos withAttributes: m_TextAttributes];
    
    m_DisplayPos.x += colMaxSize.width;
    m_DisplayPos.x += settings.getMargins().right;
    
}


- (void)drawTraceData: (TraceClientCore::CTraceData*) pTraceData
{
    NSString*           text = [[NSString alloc] initWithBytes: pTraceData->Data().c_str() length: pTraceData->Data().length()*sizeof(wchar_t) encoding: NSUTF32LittleEndianStringEncoding];
    CGSize              size = [text sizeWithAttributes: m_TextAttributes];
    CColumnSettings&    settings = m_pSettings->rgetColumnSettings( CTracesDataViewSettings::eColumn_Data );
    NSSize              colMaxSize = settings.getMaxSize();
    
    m_DisplayPos.x += settings.getMargins().left;

    colMaxSize.width = MAX(colMaxSize.width, size.width);
    colMaxSize.height = MAX(colMaxSize.height, size.height);
    
    settings.setMaxSize(colMaxSize);
    
    [text drawAtPoint:m_DisplayPos withAttributes: m_TextAttributes];

    m_DisplayPos.x += colMaxSize.width;
    m_DisplayPos.x += settings.getMargins().right;
}


@end

