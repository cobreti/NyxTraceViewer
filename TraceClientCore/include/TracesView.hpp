//
//  TracesView.hpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-19.
//
//

#ifndef TraceClientCore_TracesView_hpp
#define TraceClientCore_TracesView_hpp

#include <Nyx.hpp>
#include <list>

#include "TracesList.hpp"
#include "TracesViewNotificationsListener.hpp"

namespace TraceClientCore
{
    class CTraceChannel;
    class CTraceData;
    class CTracesViewRepoObserver;
    class CTracesView;
    
    
    /**
     *
     */
    typedef     Nyx::UInt32         TracesViewId;
    
    
    /**
     *
     */
    class CTracesViewNotificationsListeners : public ITracesViewNotificationsListener
    {
    public:
        CTracesViewNotificationsListeners();
        virtual ~CTracesViewNotificationsListeners();
        
        virtual void Add( ITracesViewNotificationsListener* pListener );
        
    public:
        virtual void OnViewBeginUpdate( CTracesView* pView );
        virtual void OnViewEndUpdate( CTracesView* pView );
        
    protected:
        
        typedef std::list<ITracesViewNotificationsListener*> TListeners;
        
    protected:
        
        TListeners          m_Listeners;
    };
    
    
    /**
     *
     */
    class CTracesView : public CTracesList
    {
        friend class CTracesViewRepoObserver;
        
    public:
        CTracesView(CTraceChannel* pChannel);
        virtual ~CTracesView();

        const TracesViewId&                         Id() const      { return m_Id; }
        
        CTraceChannel*                              Channel() const { return m_pChannel; }
        CTracesViewNotificationsListeners&          Listeners()     { return m_Listeners; }

        bool Dirty() const                                          { return m_bDirty; }
        void ResetDirty();
        
        Nyx::UInt32 LinesCount() const;

        void Clear();
        
    protected:
        
        void AddTrace( CTraceData* pTraceData );
        void BeginUpdate();
        void EndUpdate();
        
    protected:
        
        CTraceChannel*                      m_pChannel;
        CTracesViewRepoObserver*            m_pRepoObserver;
        TracesViewId                        m_Id;
        CTracesViewNotificationsListeners   m_Listeners;
        bool                                m_bDirty;
        
    protected:
        
        static TracesViewId                 s_NextId;
        
    };
}

#endif
