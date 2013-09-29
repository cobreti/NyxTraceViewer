//
//  TraceDataView.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-20.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "ViewTracesIterator.hpp"

namespace TraceClientCore
{
    class CTracesGroup;
}

class CTracesGroupListener;

@interface CTracesDataView : NSView
{
    TraceClientCore::CTracesGroup*      m_pTracesGroup;
    CTracesGroupListener*               m_pTracesGroupListener;
    CViewTracesIterator                 m_Pos;
    NSFont*                             m_pFont;
    CGFloat                             m_LineHeight;
}

- (void) onTracesGroupChanged: (TraceClientCore::CTracesGroup*)pTracesGroup;
- (void) onTracesViewBeginUpdate;
- (void) onTracesViewEndUpdate;

@end
