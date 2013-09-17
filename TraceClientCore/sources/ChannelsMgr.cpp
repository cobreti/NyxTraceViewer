//
//  ChannelsMgr.cpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-16.
//
//

#include "ChannelsMgr.hpp"

namespace TraceClientCore
{
    /**
     *
     */
    CChannelsMgr::CChannelsMgr()
    {
        m_refListenersMutex = Nyx::CMutex::Alloc();
    }
    
    
    /**
     *
     */
    CChannelsMgr::~CChannelsMgr()
    {
        
    }
    
    
    /**
     *
     */
    void CChannelsMgr::AddListener( IChannelsNotificationsListener* pListener )
    {
        Nyx::TMutexLock     lock(m_refListenersMutex, true);
        
        m_Listeners.push_back(pListener);
    }
    
    
    /**
     *
     */
    void CChannelsMgr::NotifyNewOfNewChannel( CTraceChannel* pChannel )
    {
        Nyx::TMutexLock     lock(m_refListenersMutex, true);
        
        TChannelsNotificationListeners::const_iterator          pos = m_Listeners.begin();
        
        while (pos != m_Listeners.end())
        {
            (*pos)->OnNewChannel(pChannel);
            
            ++ pos;
        }
    }
}

