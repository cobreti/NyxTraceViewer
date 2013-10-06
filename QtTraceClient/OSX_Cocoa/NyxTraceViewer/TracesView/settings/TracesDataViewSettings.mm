//
//  TracesDataViewSettings.cpp
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-29.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#include "TracesDataViewSettings.h"



/**
 *
 */
CTracesDataViewSettings::CTracesDataViewSettings()
{
    
}


CTracesDataViewSettings::CTracesDataViewSettings(const CTracesDataViewSettings& settings)
{
    m_ColumnsOrder = settings.m_ColumnsOrder;
    m_ColumnsSettings = settings.m_ColumnsSettings;
}


/**
 *
 */
CTracesDataViewSettings::~CTracesDataViewSettings()
{
    
}


const CTracesDataViewSettings& CTracesDataViewSettings::operator=(const CTracesDataViewSettings &settings)
{
    if ( this != &settings )
    {
        m_ColumnsOrder = settings.m_ColumnsOrder;
        m_ColumnsSettings = settings.m_ColumnsSettings;
    }
    
    return *this;
}