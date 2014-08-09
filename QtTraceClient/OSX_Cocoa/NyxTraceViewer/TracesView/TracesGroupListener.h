//
//  TracesGroupListener.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-22.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxTraceViewer_TracesGroupListener_h
#define NyxTraceViewer_TracesGroupListener_h

#include <objc/objc.h>
#include "TracesGroup.hpp"

@class CTracesDataView;

class CTracesGroupListener : public TraceClientCore::ITracesGroupNotificationsListener
{
public:
    CTracesGroupListener(NSObject* m_pTarget);
    virtual ~CTracesGroupListener();
    
public:
    virtual void OnViewBeginUpdate( TraceClientCore::CTracesGroup* pGroup, TraceClientCore::CTracesView* pView );
    virtual void OnViewEndUpdate( TraceClientCore::CTracesGroup* pGroup, TraceClientCore::CTracesView* pView );
    
protected:
    
    NSObject*       m_pTarget;
};


#endif
