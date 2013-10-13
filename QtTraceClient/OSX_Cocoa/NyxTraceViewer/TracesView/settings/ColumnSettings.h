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
#include <Nyx.hpp>

#include <list>


class CColumnSettings;


/**
 *
 */
class IColumnSettingsListener
{
public:
    
    virtual void OnColumnSettingsSizeChanged( CColumnSettings* pSettings ) = 0;
};


/**
 *
 */
class CColumnSettings
{
public:
    
    struct TMargins
    {
        CGFloat     left;
        CGFloat     top;
        CGFloat     right;
        CGFloat     bottom;
    };
    
public:
    CColumnSettings();
    CColumnSettings(const Nyx::CAString& title);
    CColumnSettings(const CColumnSettings& settings);
    virtual ~CColumnSettings();
    
    const NSSize&       getMaxSize() const          { return m_MaxSize; }
    void                setMaxSize(const NSSize& size);
    
    const NSSize&       getSize() const             { return m_Size; }
    void                setSize(const NSSize& size);
    
    const TMargins&     getMargins() const          { return m_Margins; }
    void                setMargins(const TMargins& margins);
    
    const Nyx::CAString&    Title() const           { return m_Title; }
    Nyx::CAString&          Title()                 { return m_Title; }
    
    const CColumnSettings& operator = (const CColumnSettings& settings);
    
    void AddListener( IColumnSettingsListener* pListener );
    
protected:
    
    typedef std::list<IColumnSettingsListener*> TListeners;
    
protected:
    
    NSSize              m_MaxSize;
    NSSize              m_Size;
    TMargins            m_Margins;
    bool                m_bAutoAdjust;
    Nyx::CAString       m_Title;
    TListeners          m_Listeners;
};


#endif /* defined(__NyxTraceViewer__ColumnSettings__) */
