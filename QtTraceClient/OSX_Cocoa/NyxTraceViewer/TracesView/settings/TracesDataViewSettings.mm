//
//  TracesDataViewSettings.cpp
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-29.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "ColumnSettingsListenerProtocol.h"

#include "TracesDataViewSettings.h"

#include <algorithm>

/**
 *
 */
CTracesDataViewSettings::CTracesDataViewSettings() :
m_LineHeight(0.0),
m_pFont(NULL)
{
}


CTracesDataViewSettings::CTracesDataViewSettings(const CTracesDataViewSettings& settings) :
m_LineHeight(settings.m_LineHeight),
m_pFont(settings.m_pFont)
{
    m_ColumnsOrder = settings.m_ColumnsOrder;
    m_ColumnsSettings = settings.m_ColumnsSettings;
    
    if ( NULL != m_pFont )
    {
        [m_pFont retain];
    }
}


/**
 *
 */
CTracesDataViewSettings::~CTracesDataViewSettings()
{
    if ( NULL != m_pFont )
    {
        [m_pFont release];
    }
}


const CTracesDataViewSettings& CTracesDataViewSettings::operator=(const CTracesDataViewSettings &settings)
{
    if ( this != &settings )
    {
        if ( NULL != settings.m_pFont )
        {
            [settings.m_pFont retain];
        }
        
        if ( NULL != m_pFont )
        {
            [m_pFont release];
        }
        
        m_ColumnsOrder = settings.m_ColumnsOrder;
        m_ColumnsSettings = settings.m_ColumnsSettings;
        m_LineHeight = settings.m_LineHeight;
        m_pFont = settings.m_pFont;
    }
    
    return *this;
}


void CTracesDataViewSettings::setFont(NSFont* pFont)
{
    if (NULL != pFont)
        [pFont retain];
    
    if (NULL != m_pFont)
        [m_pFont release];
    
    m_pFont = pFont;
    m_LineHeight = [m_pFont ascender] - [m_pFont descender] + 5;
}


void CTracesDataViewSettings::setColumnsOrder(const CTracesDataViewSettings::TColumnsOrder &order)
{
    m_ColumnsOrder = order;
}


void CTracesDataViewSettings::setColumnSettings(CTracesDataViewSettings::EColumns col, const CColumnSettings &settings)
{
    m_ColumnsSettings[col] = settings;
    m_ColumnsSettings[col].AddListener( static_cast<IColumnSettingsListener*>(this) );
}


NSSize CTracesDataViewSettings::getMaxLineSize() const
{
    NSSize  size = NSZeroSize;
    
    size_t  count = m_ColumnsOrder.size();
    size_t  index = 0;
    
    while ( index < count )
    {
        EColumns                    col = m_ColumnsOrder[index];
        const CColumnSettings&      rColSettings = m_ColumnsSettings.at(col);
        CGFloat                     height;
        
        size.width += rColSettings.getMargins().left + rColSettings.getMaxSize().width + rColSettings.getMargins().right;
        height = rColSettings.getMargins().top + rColSettings.getMaxSize().height + rColSettings.getMargins().bottom;
        
        size.height = MAX(size.height, height);
        
        ++ index;
    }
    
    return size;
}


/**
 *
 */
void CTracesDataViewSettings::OnColumnSettingsSizeChanged(CColumnSettings *pSettings)
{
    auto delegate = [pSettings] (NSObject* pListener) {
        if ( [pListener conformsToProtocol:@protocol(CColumnSettingsListenerProtocol)] )
        {
            [(NSObject<CColumnSettingsListenerProtocol>*) pListener onColumnSettingsSizeChanged: pSettings];
        }
    };
    
    std::for_each(m_ColumnsSettingsListener.begin(), m_ColumnsSettingsListener.end(), delegate);    
}


/**
 *
 */
void CTracesDataViewSettings::AddColumnsSettingsListener(NSObject *pListener)
{
    m_ColumnsSettingsListener.push_back(pListener);
}

