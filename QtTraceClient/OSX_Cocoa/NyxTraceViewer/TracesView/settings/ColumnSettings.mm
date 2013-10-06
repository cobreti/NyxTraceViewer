//
//  ColumnSettings.cpp
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-29.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#include "ColumnSettings.h"


/**
 *
 */
CColumnSettings::CColumnSettings() :
m_bAutoAdjust(true)
{
    m_MaxSize = NSZeroRect;
    m_Size = NSZeroRect;
}


CColumnSettings::CColumnSettings(const CColumnSettings& settings) :
m_MaxSize(settings.m_MaxSize),
m_Size(settings.m_Size),
m_bAutoAdjust(settings.m_bAutoAdjust)
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
        m_bAutoAdjust = settings.m_bAutoAdjust;
    }
    
    return *this;
}