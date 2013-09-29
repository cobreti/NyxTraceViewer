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


/**
 *
 */
CColumnSettings::~CColumnSettings()
{
}

