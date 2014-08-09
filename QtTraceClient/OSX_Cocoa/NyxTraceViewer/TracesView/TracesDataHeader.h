//
//  TraceDataHeader.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-10-12.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "settings/ColumnSettingsListenerProtocol.h"

class CTracesDataViewSettings;

@interface CTracesDataHeader : NSView <CColumnSettingsListenerProtocol>
{
    CTracesDataViewSettings*        m_pSettings;
    NSFont*                         m_pFont;
    CGFloat                         m_TopMargin;
    CGFloat                         m_BottomMargin;
}

- (void) setSettings: (CTracesDataViewSettings*)pSettings;
- (void) initMinColsSize;

- (void)onColumnSettingsSizeChanged: (CColumnSettings*) pSettings;

@end
