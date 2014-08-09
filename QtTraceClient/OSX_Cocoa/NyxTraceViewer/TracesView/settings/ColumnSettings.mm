//
//  ColumnSettings.cpp
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-29.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#include "ColumnSettings.h"

#include <algorithm>

/**
 *
 */
CColumnSettings::CColumnSettings() :
m_bAutoAdjust(true)
{
    m_MaxSize = NSZeroSize;
    m_Size = NSZeroSize;
    m_Margins = {10, 0, 20, 0};
}


/**
 *
 */
CColumnSettings::CColumnSettings(const Nyx::CAString& title) :
m_bAutoAdjust(true),
m_Title(title)
{
    m_MaxSize = NSZeroSize;
    m_Size = NSZeroSize;
    m_Margins = {10, 0, 20, 0};    
}


CColumnSettings::CColumnSettings(const CColumnSettings& settings) :
m_MaxSize(settings.m_MaxSize),
m_Size(settings.m_Size),
m_Margins(settings.m_Margins),
m_bAutoAdjust(settings.m_bAutoAdjust),
m_Title(settings.m_Title),
m_Listeners(settings.m_Listeners)
{
    
}


/**
 *
 */
CColumnSettings::~CColumnSettings()
{

}


/**
 *
 */
const CColumnSettings& CColumnSettings::operator = (const CColumnSettings& settings)
{
    if ( this != &settings )
    {
        m_MaxSize = settings.m_MaxSize;
        m_Size = settings.m_Size;
        m_Margins = settings.m_Margins;
        m_bAutoAdjust = settings.m_bAutoAdjust;
        m_Title = settings.m_Title;
        m_Listeners = settings.m_Listeners;
    }
    
    return *this;
}


/**
 *
 */
void CColumnSettings::setMaxSize(const NSSize &size)
{
    m_MaxSize = size;
    
    if ( m_bAutoAdjust )
    {
        if (size.width > m_Size.width || size.height > m_Size.height)
        {
            m_Size.width = MAX(m_Size.width, size.width);
            m_Size.height = MAX(m_Size.height, size.height);

            auto listener_call = [this] (IColumnSettingsListener* pListener) {
                pListener->OnColumnSettingsSizeChanged(this);
            };
            
            std::for_each( m_Listeners.begin(), m_Listeners.end(), listener_call );
        }
        
    }
}


/**
 *
 */
void CColumnSettings::setSize(const NSSize &size)
{
    m_Size = size;
}


/**
 *
 */
void CColumnSettings::setMargins(const CColumnSettings::TMargins& margins)
{
    m_Margins = margins;
}


/**
 *
 */
void CColumnSettings::AddListener(IColumnSettingsListener *pListener)
{
    m_Listeners.push_back(pListener);
}


