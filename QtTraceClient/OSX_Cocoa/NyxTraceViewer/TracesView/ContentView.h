//
//  ContentView.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-20.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "TracesGroupListener.h"
#import "settings/TracesDataViewSettings.h"


namespace TraceClientCore
{
    class CTracesGroup;
}

@class CTracesDataView;

@interface CContentView : NSView
{
    NSScrollView*                   m_TracesScrollView;
    CTracesDataView*                m_TracesDataView;
    CTracesDataViewSettings         m_Settings;
}

- (void) createTracesScrollView;
- (void) createTracesDataView;
- (void) initSettings;
- (void) onTracesGroupChanged: (TraceClientCore::CTracesGroup*)pTracesGroup;

@end
