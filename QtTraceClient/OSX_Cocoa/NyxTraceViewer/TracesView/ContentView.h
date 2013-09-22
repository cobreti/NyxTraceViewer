//
//  ContentView.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-20.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

namespace TraceClientCore
{
    class CTracesGroup;
}

@class CTracesDataView;

@interface CContentView : NSView
{
    NSScrollView*       m_TracesScrollView;
    CTracesDataView*    m_TracesDataView;
}

- (void) createTracesScrollView;
- (void) createTracesDataView;
- (void) onTracesGroupChanged: (TraceClientCore::CTracesGroup*)pTracesGroup;

@end
