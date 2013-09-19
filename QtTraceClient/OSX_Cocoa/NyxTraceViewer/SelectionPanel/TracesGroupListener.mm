//
//  TracesGroupListener.mm
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-19.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "SelectionPanel.h"

#include "TracesGroupListener.h"


/**
 *
 */
CTracesGroupListener::CTracesGroupListener( CSelectionPanel* pPanel ) :
m_pPanel(pPanel)
{
    
}


/**
 *
 */
CTracesGroupListener::~CTracesGroupListener()
{
    
}


/**
 *
 */
void CTracesGroupListener::OnNewTracesGroup( TraceClientCore::CTracesGroup* pGroup )
{
    NSDictionary*       params = [[NSDictionary alloc] initWithObjectsAndKeys: [NSValue valueWithPointer: pGroup], @"tracesgroup", nil];
    
    [m_pPanel performSelectorOnMainThread: @selector(onNewTracesGroup:) withObject: params waitUntilDone: NO];
}


/**
 *
 */
void CTracesGroupListener::OnTracesGroupWillBeDeleted( TraceClientCore::CTracesGroup* pGroup )
{
    
    NSDictionary*       params = [[NSDictionary alloc] initWithObjectsAndKeys: [NSValue valueWithPointer: pGroup], @"tracesgroup", nil];
    
    [m_pPanel performSelectorOnMainThread: @selector(OnTracesGroupWillBeDeleted:) withObject: params waitUntilDone: NO];
}
