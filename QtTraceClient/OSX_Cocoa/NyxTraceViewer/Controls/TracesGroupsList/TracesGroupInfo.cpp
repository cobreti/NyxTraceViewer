//
//  TracesGroupInfo.cpp
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-09.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#include "TracesGroupInfo.h"
#include "TraceClientCoreModule.hpp"


CTracesGroupInfo::CTracesGroupInfo( TraceClientCore::CTracesGroup* pGroup ) :
m_pGroup(pGroup),
m_Name(pGroup->Name())
{
    
}


CTracesGroupInfo::~CTracesGroupInfo()
{
    
}

