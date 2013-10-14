//
//  TraceLineDisplay.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-10-07.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Foundation/Foundation.h>

#include "ViewTracesIterator.hpp"

class CTracesDataViewSettings;

@interface CTraceLineDisplay : NSObject
{
    CViewTracesIterator             m_TracePos;
    NSRect                          m_DisplayRect;
    NSRect                          m_ViewRect;
    CTracesDataViewSettings*        m_pSettings;
    NSPoint                         m_MaxPos;
    
    NSDictionary*                   m_TextAttributes;
    
}


- (id)init;
- (void)dealloc;
- (void)setTracePos: (const CViewTracesIterator&)TracePos;
- (const CViewTracesIterator&) getTracePos;
- (void)setDisplayPos: (NSPoint) DisplayPos;
- (NSPoint)getDisplayPos;
- (void)setViewRect: (NSRect)ViewRect;
- (NSRect)getViewRect;
- (void)setSettings: (CTracesDataViewSettings*) pSettings;

- (void)prepareForDrawing;
- (BOOL)doneDrawing;
- (void)drawLine;

@end
