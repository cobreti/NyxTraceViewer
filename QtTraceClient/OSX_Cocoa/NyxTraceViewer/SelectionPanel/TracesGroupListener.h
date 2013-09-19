//
//  TracesGroupListener.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-19.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxTraceViewer_TracesGroupListener_h
#define NyxTraceViewer_TracesGroupListener_h

#include <Nyx.hpp>
#include "TraceClientCoreModule.hpp"


@class CSelectionPanel;

class CTracesGroupListener : public TraceClientCore::ITracesGroupNotificationsListener
{
public:
    CTracesGroupListener( CSelectionPanel* pPanel );
    virtual ~CTracesGroupListener();
    
public:
    
    virtual void OnNewTracesGroup( TraceClientCore::CTracesGroup* pGroup );
    virtual void OnTracesGroupWillBeDeleted( TraceClientCore::CTracesGroup* pGroup );
    
protected:
    
    CSelectionPanel*        m_pPanel;
};

#endif

