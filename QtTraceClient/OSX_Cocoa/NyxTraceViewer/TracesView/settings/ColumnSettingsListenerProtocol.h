//
//  ColumnSettingsListenerProtocol.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-10-12.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Foundation/Foundation.h>

class CColumnSettings;

@protocol CColumnSettingsListenerProtocol <NSObject>

- (void)onColumnSettingsSizeChanged: (CColumnSettings*) pSettings;

@end
