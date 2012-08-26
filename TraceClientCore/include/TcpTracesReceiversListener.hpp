#ifndef _ITCPTRACESRECEIVERSLISTENER_HPP_
#define _ITCPTRACESRECEIVERSLISTENER_HPP_

#include <Nyx.hpp>

#include <map>


DECLARE_NSPOBJECTREF(TraceClientCore, ITcpTracesReceiversListener)
DECLARE_NSPOBJECTREF(TraceClientCore, CTcpTracesReceiversListeners)


namespace TraceClientCore
{
    /**
     *
     */
    class ITcpTracesReceiversListener : public Nyx::CObject
    {
    public:
        
        virtual void OnReceiversStarted() = 0;
        virtual void OnReceiversStopped() = 0;
    };

    /**
     *
     */
    class CTcpTracesReceiversListeners : public Nyx::CObject_Impl<ITcpTracesReceiversListener>
    {
    protected:
        
        typedef std::map<ITcpTracesReceiversListener*, ITcpTracesReceiversListenerRef> ListenersMap;
        
    public:
        CTcpTracesReceiversListeners() {}
        virtual ~CTcpTracesReceiversListeners() {}
        
        
        void Add( ITcpTracesReceiversListener* pListener )
        {
            if ( m_Listeners.count(pListener) == 0 )
                m_Listeners.insert( std::make_pair(pListener, pListener) );
        }
        
        void Remove( ITcpTracesReceiversListener* pListener )
        {
            ListenersMap::iterator      pos = m_Listeners.find(pListener);
            
            if ( pos != m_Listeners.end() )
                m_Listeners.erase(pos);
        }
        
        void Clear()
        {
            m_Listeners.clear();
        }
        
        
        virtual void OnReceiversStarted()
        {
            ListenersMap::iterator      pos = m_Listeners.begin();
            
            while ( pos != m_Listeners.end() )
            {
                pos->second->OnReceiversStarted();
                ++ pos;
            }
        }
        
        virtual void OnReceiversStopped()
        {
            ListenersMap::iterator      pos = m_Listeners.begin();
            
            while ( pos != m_Listeners.end() )
            {
                pos->second->OnReceiversStopped();
                ++ pos;
            }
        }
        
    protected:
        
        ListenersMap        m_Listeners;
    };
}


#endif // _ITCPTRACESRECEIVERSLISTENER_HPP_
