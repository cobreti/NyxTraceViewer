//
//  ColumnSettings.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-29.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef __NyxTraceViewer__ColumnSettings__
#define __NyxTraceViewer__ColumnSettings__

#include <objc/objc.h>

class CColumnSettings
{
public:
    CColumnSettings();
    virtual ~CColumnSettings();
    
protected:
    
    NSRect          m_MaxSize;
    NSRect          m_Size;
    bool            m_bAutoAdjust;
};


#endif /* defined(__NyxTraceViewer__ColumnSettings__) */
