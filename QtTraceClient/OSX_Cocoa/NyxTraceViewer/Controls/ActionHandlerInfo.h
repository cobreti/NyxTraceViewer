//
//  ActionHandlerInfo.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-08.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef __NyxTraceViewer__ActionHandlerInfo__
#define __NyxTraceViewer__ActionHandlerInfo__

#include <objc/objc.h>

class CActionHandlerInfo
{
public:
    CActionHandlerInfo();
    CActionHandlerInfo(SEL selector, id target);
    CActionHandlerInfo(const CActionHandlerInfo& info);
    ~CActionHandlerInfo();
  
    const CActionHandlerInfo& operator = (const CActionHandlerInfo& info);
    
    SEL     Selector() const        { return m_Selector; }
    id      Target() const          { return m_Target; }
    
    bool    Valid() const           { return m_Selector != nullptr && m_Target != nullptr; }
    
private:
    SEL         m_Selector;
    id          m_Target;
};


#endif /* defined(__NyxTraceViewer__ActionHandlerInfo__) */
