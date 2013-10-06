//
//  TracesGroupListener.mm
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-22.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//


#include "TracesGroupListener.h"
#include "TracesDataView.h"


CTracesGroupListener::CTracesGroupListener(NSObject* pTarget) :
m_pTarget(pTarget)
{
}


CTracesGroupListener::~CTracesGroupListener()
{
    
}


void CTracesGroupListener::OnViewBeginUpdate(TraceClientCore::CTracesGroup *pGroup, TraceClientCore::CTracesView *pView)
{
    if ( [m_pTarget conformsToProtocol:@protocol(CTracesGroupListenerProtocol)] )
    {
        [ (NSObject<CTracesGroupListenerProtocol>*) m_pTarget onTracesViewBeginUpdate];
    }
}


void CTracesGroupListener::OnViewEndUpdate(TraceClientCore::CTracesGroup *pGroup, TraceClientCore::CTracesView *pView)
{
    if ( [m_pTarget conformsToProtocol:@protocol(CTracesGroupListenerProtocol)] )
    {
        [(NSObject<CTracesGroupListenerProtocol>*) m_pTarget onTracesViewEndUpdate];
    }
}

