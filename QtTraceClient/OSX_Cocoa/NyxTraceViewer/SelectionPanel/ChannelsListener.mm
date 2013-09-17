//
//  ChannelsListener.cpp
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-16.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "SelectionPanel.h"

#include "ChannelsListener.h"


/**
 *
 */
CChannelsListener::CChannelsListener(CSelectionPanel* pPanel) :
m_pPanel(pPanel)
{
    
}


/**
 *
 */
CChannelsListener::~CChannelsListener()
{
    
}



void CChannelsListener::OnNewChannel( TraceClientCore::CTraceChannel* pChannel )
{
    NYXTRACE(0x0, L"CChannelsListener::OnNewChannel");
    
    NSDictionary*       params = [[NSDictionary alloc] initWithObjectsAndKeys: [NSValue valueWithPointer: pChannel], @"channel", nil];
    
    [m_pPanel performSelectorOnMainThread: @selector(onNewChannel:) withObject:params waitUntilDone:NO];
}

