//
//  TracesViewNotificationsListener.hpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-21.
//
//

#ifndef TraceClientCore_TracesViewNotificationsListener_hpp
#define TraceClientCore_TracesViewNotificationsListener_hpp


namespace TraceClientCore
{
    class CTracesView;
    
    
    /**
     *
     */
    class ITracesViewNotificationsListener
    {
    public:
        virtual void OnViewBeginUpdate( CTracesView* pView ) = 0;
        virtual void OnViewEndUpdate( CTracesView* pView ) = 0;
    };
    
    
}


#endif
