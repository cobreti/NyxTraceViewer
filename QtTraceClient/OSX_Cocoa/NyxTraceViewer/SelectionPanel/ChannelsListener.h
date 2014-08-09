//
//  ChannelsListener.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-16.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef __NyxTraceViewer__ChannelsListener__
#define __NyxTraceViewer__ChannelsListener__

#include "TraceClientCoreModule.hpp"

@class CSelectionPanel;

class CChannelsListener : public TraceClientCore::IChannelsNotificationsListener
{
public:
    CChannelsListener(CSelectionPanel* pPanel);
    virtual ~CChannelsListener();
    
public: // IChannelsNotificationsListener
    
    virtual void OnNewChannel( TraceClientCore::CTraceChannel* pChannel );
    
    
protected:
    
    CSelectionPanel*      m_pPanel;
};


#endif /* defined(__NyxTraceViewer__ChannelsListener__) */
