//
//  TracesGroupListener.mm
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-22.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#include "TracesGroupListener.h"
#include "TracesDataView.h"


CTracesGroupListener::CTracesGroupListener(CTracesDataView* pView) :
m_pView(pView)
{
    
}


CTracesGroupListener::~CTracesGroupListener()
{
    
}


void CTracesGroupListener::OnViewBeginUpdate(TraceClientCore::CTracesGroup *pGroup, TraceClientCore::CTracesView *pView)
{
    [m_pView onTracesViewBeginUpdate];
}


void CTracesGroupListener::OnViewEndUpdate(TraceClientCore::CTracesGroup *pGroup, TraceClientCore::CTracesView *pView)
{
    [m_pView onTracesViewEndUpdate];
}

