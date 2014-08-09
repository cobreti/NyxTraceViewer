//
//  TraceDataView.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-20.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "ViewTracesIterator.hpp"
#import "TracesGroupListenerProtocol.h"

namespace TraceClientCore
{
    class CTracesGroup;
}

class CTracesDataViewSettings;
class CTracesGroupListener;

@interface CTracesDataView : NSView <CTracesGroupListenerProtocol>
{
    TraceClientCore::CTracesGroup*      m_pTracesGroup;
    CTracesGroupListener*               m_pTracesGroupListener;
    CViewTracesIterator                 m_Pos;
    NSRect                              m_LastVisibleRect;
    NSRect                              m_LastFrame;
    CTracesDataViewSettings*            m_pSettings;
}

- (void) onTracesGroupChanged: (TraceClientCore::CTracesGroup*)pTracesGroup;
- (void) onTracesViewBeginUpdate;
- (void) onTracesViewEndUpdate;
- (void) setSettings: (CTracesDataViewSettings*)pSettings;

@end
