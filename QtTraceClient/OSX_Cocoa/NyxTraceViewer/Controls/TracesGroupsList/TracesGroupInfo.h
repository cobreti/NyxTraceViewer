//
//  TracesGroupInfo.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-09.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef __NyxTraceViewer__TracesGroupInfo__
#define __NyxTraceViewer__TracesGroupInfo__

#include <Nyx.hpp>

namespace TraceClientCore
{
    class CTracesGroup;
}


class CTracesGroupInfo
{
public:
    CTracesGroupInfo(TraceClientCore::CTracesGroup* pGroup);
    ~CTracesGroupInfo();
    
    const Nyx::CAString& Name() const           { return m_Name; }
    Nyx::CAString& Name()                       { return m_Name; }
    
    TraceClientCore::CTracesGroup*      Group() const           { return m_pGroup; }
    
protected:
    
    Nyx::CAString                       m_Name;
    TraceClientCore::CTracesGroup*      m_pGroup;
};

#endif /* defined(__NyxTraceViewer__TracesGroupInfo__) */
