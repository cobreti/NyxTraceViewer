//
//  ChannelsMgr.hpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-16.
//
//

#ifndef TraceClientCore_ChannelsMgr_hpp
#define TraceClientCore_ChannelsMgr_hpp

#include <Nyx.hpp>

#include <list>


namespace TraceClientCore
{
    class CTraceChannel;
    
    
    /**
     *
     */
    class IChannelsNotificationsListener
    {
    public:
        
        virtual void OnNewChannel( CTraceChannel* pChannel ) = 0;
    };
    
    
    /**
     *
     */
    class CChannelsMgr
    {
    public:
        CChannelsMgr();
        virtual ~CChannelsMgr();
        
        void AddListener( IChannelsNotificationsListener* pListener );

        void OnNewChannel( CTraceChannel* pChannel );
        
    protected:
        
        typedef std::list<IChannelsNotificationsListener*>  TChannelsNotificationListeners;

    protected:
        
        void NotifyOfNewChannel( CTraceChannel* pChannel );

    protected:
        
        Nyx::CMutexRef                          m_refListenersMutex;
        TChannelsNotificationListeners          m_Listeners;
    };
}


#endif
