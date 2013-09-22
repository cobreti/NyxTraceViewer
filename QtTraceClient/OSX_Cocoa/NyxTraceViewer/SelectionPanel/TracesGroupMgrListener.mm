//
//  TracesGroupListener.mm
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-19.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "SelectionPanel.h"

#include "TracesGroupMgrListener.h"


/**
 *
 */
CTracesGroupMgrListener::CTracesGroupMgrListener( CSelectionPanel* pPanel ) :
m_pPanel(pPanel)
{
    
}


/**
 *
 */
CTracesGroupMgrListener::~CTracesGroupMgrListener()
{
    
}


/**
 *
 */
void CTracesGroupMgrListener::OnNewTracesGroup( TraceClientCore::CTracesGroup* pGroup )
{
    NSDictionary*       params = [[NSDictionary alloc] initWithObjectsAndKeys: [NSValue valueWithPointer: pGroup], @"tracesgroup", nil];
    
    [m_pPanel performSelectorOnMainThread: @selector(onNewTracesGroup:) withObject: params waitUntilDone: NO];
}


/**
 *
 */
void CTracesGroupMgrListener::OnTracesGroupWillBeDeleted( TraceClientCore::CTracesGroup* pGroup )
{
    
    NSDictionary*       params = [[NSDictionary alloc] initWithObjectsAndKeys: [NSValue valueWithPointer: pGroup], @"tracesgroup", nil];
    
    [m_pPanel performSelectorOnMainThread: @selector(OnTracesGroupWillBeDeleted:) withObject: params waitUntilDone: NO];
}
