//
//  TracesDataViewSettings.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-29.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef __NyxTraceViewer__TracesDataViewSettings__
#define __NyxTraceViewer__TracesDataViewSettings__

#include "ColumnSettings.h"

#include <map>
#include <vector>

class CTracesDataViewSettings
{
public:
    
    enum EColumns
    {
        eColumn_LineNumber = 0,
        eColumn_Data,
        eColumnsCount
    };
    
    typedef     std::vector<EColumns>       TColumnsOrder;
    
public:
    CTracesDataViewSettings();
    CTracesDataViewSettings(const CTracesDataViewSettings& settings);
    virtual ~CTracesDataViewSettings();
    
    const CTracesDataViewSettings& operator = (const CTracesDataViewSettings& settings);
    
protected:
    
    typedef     std::map<EColumns, CColumnSettings>     TColumnsSettingsTable;
    
protected:
    
    TColumnsOrder               m_ColumnsOrder;
    TColumnsSettingsTable       m_ColumnsSettings;
};

#endif /* defined(__NyxTraceViewer__TracesDataViewSettings__) */
