//
//  TraceDataHeader.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-10-12.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "TracesDataHeader.h"
#import "settings/TracesDataViewSettings.h"

@implementation CTracesDataHeader

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {

        m_pFont = [NSFont fontWithName: @"Arial" size: 12];
        m_TopMargin = 5;
        m_BottomMargin = 10;
        
        CGFloat     height = [m_pFont ascender] - [m_pFont descender] + m_TopMargin + m_BottomMargin;
        frame.size.height = height;
        
        [self setFrame: frame];
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

    CTracesDataViewSettings::TColumnsOrder      columnsOrder = m_pSettings->getColumnsOrder();
    size_t                                      index = 0;
    NSRect                                      rc = NSZeroRect;

    rc.origin.y = m_TopMargin;
    
    NSDictionary*                               textAttributes = [[NSDictionary alloc] initWithObjectsAndKeys: m_pFont, NSFontAttributeName, [NSColor blackColor], NSForegroundColorAttributeName, nil];;

    while (index < columnsOrder.size())
    {
        CTracesDataViewSettings::EColumns       col = columnsOrder[index];
        CColumnSettings&                        rSettings = m_pSettings->rgetColumnSettings(col);
        
        rc.size = rSettings.getSize();
        rc.origin.x += rSettings.getMargins().left;
        
        if ( rc.size.width > 1 )
        {
            NSString*   text = [[NSString alloc] initWithCString: rSettings.Title().c_str() encoding: NSMacOSRomanStringEncoding];
            
            [text drawInRect: rc withAttributes:textAttributes];
        }
        
        rc.origin.x += rc.size.width;
        rc.origin.x += rSettings.getMargins().right;
        
        ++ index;
    }
    
    [textAttributes release];
    
}

- (void) setSettings: (CTracesDataViewSettings*)pSettings
{
    m_pSettings = pSettings;
    
    m_pSettings->AddColumnsSettingsListener(self);
}

- (void)onColumnSettingsSizeChanged: (CColumnSettings*) pSettings
{
    NYXTRACE(0x0, L"column " << Nyx::CTF_AnsiText(pSettings->Title().c_str()) << L" size changed" );

    [self setNeedsDisplay:YES];
}

@end
