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

class CTracesGroupInfo
{
public:
    CTracesGroupInfo();
    CTracesGroupInfo(const Nyx::CAString& name);
    ~CTracesGroupInfo();
    
    const Nyx::CAString& Name() const           { return m_Name; }
    Nyx::CAString& Name()                       { return m_Name; }
    
protected:
    
    Nyx::CAString           m_Name;
};

#endif /* defined(__NyxTraceViewer__TracesGroupInfo__) */
