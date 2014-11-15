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
    class ITracesGroupMgrNotificationsListener
    {
    public:
        
        virtual void OnNewTracesGroup( CTracesGroup* pGroup ) = 0;
        virtual void OnTracesGroupWillBeDeleted( CTracesGroup* pGroup ) = 0;
    };
    
    
    
    /**
     *
     */
    class CTracesGroupMgrNotificationsListeners : public ITracesGroupMgrNotificationsListener
    {
    public:
        CTracesGroupMgrNotificationsListeners();
        virtual ~CTracesGroupMgrNotificationsListeners();
        
        void Add( ITracesGroupMgrNotificationsListener* pListener );
        void Remove( ITracesGroupMgrNotificationsListener* pListener );

    public:
        virtual void OnNewTracesGroup( CTracesGroup* pGroup );
        virtual void OnTracesGroupWillBeDeleted( CTracesGroup* pGroup );
        
    protected:
        
        typedef         std::list<ITracesGroupMgrNotificationsListener*>           TListenersList;
        
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
        
        CTracesGroup* GetGroup(const QString& name) const;

        CTracesGroup* CreateTracesGroup(const QString& name);
        void ReleaseTracesGroup( CTracesGroup* pTracesGroup );
        
        CTracesGroupMgrNotificationsListeners&     Listeners()         { return m_Listeners; }
        
    protected:
        
        typedef     std::map<TracesGroupId, CTracesGroup*>          TTracesGroupMap;
        
    protected:
        
        TTracesGroupMap                         m_TracesGroups;
        CTracesGroupMgrNotificationsListeners   m_Listeners;
    };
}


#endif
