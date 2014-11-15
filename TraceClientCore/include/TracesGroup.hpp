//
//  TracesGroup.hpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-18.
//
//

#ifndef TraceClientCore_TracesGroup_hpp
#define TraceClientCore_TracesGroup_hpp

#include <Nyx.hpp>
#include "TracesViewNotificationsListener.hpp"

#include <list>
#include <QtCore>

namespace TraceClientCore
{
    class CTraceChannel;
    class CTracesView;
    class CTracesGroup;
    class CMultiViewTracesIterator;
    
    
    /**
     *
     */
    typedef     Nyx::UInt32         TracesGroupId;
    
    
    
    /**
     *
     */
    class ITracesGroupNotificationsListener
    {
    public:
        virtual void OnViewBeginUpdate( CTracesGroup* pGroup, CTracesView* pView ) = 0;
        virtual void OnViewEndUpdate( CTracesGroup* pGroup, CTracesView* pView ) = 0;
    };
    

    
    /**
     *
     */
    class CTracesGroupNotificationsListeners : public ITracesGroupNotificationsListener
    {
    public:
        CTracesGroupNotificationsListeners();
        virtual ~CTracesGroupNotificationsListeners();
        
        virtual void Add( ITracesGroupNotificationsListener* pListener );
        virtual void Remove( ITracesGroupNotificationsListener* pListener );

    public:
        virtual void OnViewBeginUpdate( CTracesGroup* pGroup, CTracesView* pView );
        virtual void OnViewEndUpdate( CTracesGroup* pGroup, CTracesView* pView );
        
    protected:
        
        typedef     std::list<ITracesGroupNotificationsListener*>       TTracesGroupListeners;
        
    protected:
        
        TTracesGroupListeners           m_Listeners;
    };
    
    
    
    /**
     *
     */
    class CTracesGroup : public ITracesViewNotificationsListener
    {
        friend class CTracesGroupMgr;
        
    public:
        const TracesGroupId&        Id() const                          { return m_Id; }
        
        const QString&    Name() const                                  { return m_Name; }
        QString&          Name()                                        { return m_Name; }
        
        CTracesGroupNotificationsListeners&     Listeners()             { return m_Listeners; }
        
        void AddChannel( CTraceChannel* pChannel );
        bool HasChannel( CTraceChannel* pChannel );
        
        CMultiViewTracesIterator FirstPos();
        CMultiViewTracesIterator LastPos();
        
        Nyx::UInt32 LinesCount() const;

        void Clear();
        
    public:
        
        virtual void OnViewBeginUpdate( CTracesView* pView );
        virtual void OnViewEndUpdate( CTracesView* pView );

    protected:
        
        typedef     std::list<CTracesView*>     TTracesViews;
        
    protected:
        
        CTracesGroup();
        virtual ~CTracesGroup();
        
        
    protected:
        
        TracesGroupId                           m_Id;
        QString                                 m_Name;
        TTracesViews                            m_Views;
        CTracesGroupNotificationsListeners      m_Listeners;
        
    private:
        
        static TracesGroupId        s_NextAvailId;
    };
}


#endif
