//
//  ActionHandlerInfo.cpp
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-08.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#include "ActionHandlerInfo.h"


CActionHandlerInfo::CActionHandlerInfo() :
m_Selector(nullptr),
m_Target(nullptr)
{
    
}


CActionHandlerInfo::CActionHandlerInfo(SEL selector, id target) :
m_Selector(selector),
m_Target(target)
{
    
}


CActionHandlerInfo::CActionHandlerInfo(const CActionHandlerInfo& info) :
m_Selector(info.m_Selector),
m_Target(info.m_Target)
{

}


CActionHandlerInfo::~CActionHandlerInfo()
{
}


const CActionHandlerInfo& CActionHandlerInfo::operator = (const CActionHandlerInfo& info)
{
    m_Selector = info.m_Selector;
    m_Target = info.m_Target;
    
    return *this;
}