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
#include <list>


class CTracesDataViewSettings : public IColumnSettingsListener
{
public:
    
    enum EColumns
    {
        eColumn_LineNumber = 0,
        eColumn_TickCount,
        eColumn_ThreadId,
        eColumn_Data,
        eColumnsCount
    };
    
    typedef     std::vector<EColumns>       TColumnsOrder;
    
public:
    CTracesDataViewSettings();
    CTracesDataViewSettings(const CTracesDataViewSettings& settings);
    virtual ~CTracesDataViewSettings();
    
    const CTracesDataViewSettings& operator = (const CTracesDataViewSettings& settings);
    
    void setFont( NSFont* pFont );
    NSFont* getFont() const                 { return m_pFont; }
    
    CGFloat     getLineHeight() const       { return m_LineHeight; }
    
    const TColumnsOrder&        getColumnsOrder() const             { return m_ColumnsOrder; }
    void                        setColumnsOrder(const TColumnsOrder& order);
    
    CColumnSettings&            rgetColumnSettings(EColumns col)        { return m_ColumnsSettings[col]; }
    const CColumnSettings&      getColumnSettings(EColumns col) const   { return m_ColumnsSettings.at(col); }
    void                        setColumnSettings(EColumns col, const CColumnSettings& settings);
    
    NSSize                      getMaxLineSize() const;
    
    void AddColumnsSettingsListener(NSObject* pListener);
    
public:
    
    virtual void OnColumnSettingsSizeChanged( CColumnSettings* pSettings );
    
protected:
    
    typedef     std::map<EColumns, CColumnSettings>                             TColumnsSettingsTable;
    typedef     std::list<NSObject*>                                            TColumnsSettingsListeners;
    
protected:
    
    TColumnsOrder               m_ColumnsOrder;
    TColumnsSettingsTable       m_ColumnsSettings;
    CGFloat                     m_LineHeight;
    NSFont*                     m_pFont;
    TColumnsSettingsListeners   m_ColumnsSettingsListener;
};

#endif /* defined(__NyxTraceViewer__TracesDataViewSettings__) */
