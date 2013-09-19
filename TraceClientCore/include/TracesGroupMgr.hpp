//
//  TracesGroupMgr.hpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-18.
//
//

#ifndef TraceClientCore_TracesGroupMgr_hpp
#define TraceClientCore_TracesGroupMgr_hpp

#include "TracesGroup.hpp"

#include <map>
#include <list>


namespace TraceClientCore
{
    
    /**
     *
     */
    class ITracesGroupNotificationsListener
    {
    public:
        
        virtual void OnNewTracesGroup( CTracesGroup* pGroup ) = 0;
        virtual void OnTracesGroupWillBeDeleted( CTracesGroup* pGroup ) = 0;
    };
    
    
    
    /**
     *
     */
    class CTracesGroupNotificationsListeners : public ITracesGroupNotificationsListener
    {
    public:
        CTracesGroupNotificationsListeners();
        virtual ~CTracesGroupNotificationsListeners();
        
        void Add( ITracesGroupNotificationsListener* pListener );
        void Remove( ITracesGroupNotificationsListener* pListener );

    public:
        virtual void OnNewTracesGroup( CTracesGroup* pGroup );
        virtual void OnTracesGroupWillBeDeleted( CTracesGroup* pGroup );
        
    protected:
        
        typedef         std::list<ITracesGroupNotificationsListener*>           TListenersList;
        
    protected:
        
        TListenersList          m_Listeners;
    };
    
    
    
    /**
     *
     */
    class CTracesGroupMgr
    {
    public:
        CTracesGroupMgr();
        virtual ~CTracesGroupMgr();
        
        CTracesGroup* CreateTracesGroup(const Nyx::CAString& name);
        void ReleaseTracesGroup( CTracesGroup* pTracesGroup );
        
        CTracesGroupNotificationsListeners&     Listeners()         { return m_Listeners; }
        
    protected:
        
        typedef     std::map<TracesGroupId, CTracesGroup*>          TTracesGroupMap;
        
    protected:
        
        TTracesGroupMap                         m_TracesGroups;
        CTracesGroupNotificationsListeners      m_Listeners;
    };
}


#endif
