//
//  TracesGroupMgr.cpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-18.
//
//

#include "TracesGroupMgr.hpp"


namespace TraceClientCore
{
    
    /**
     *
     */
    CTracesGroupMgr::CTracesGroupMgr()
    {
        
    }
    
    
    /**
     *
     */
    CTracesGroupMgr::~CTracesGroupMgr()
    {
        
    }
    
    
    /**
     * @brief CTracesGroupMgr::GetGroup
     * @param name
     * @return
     */
    CTracesGroup* CTracesGroupMgr::GetGroup(const QString& name) const
    {
        TTracesGroupMap::const_iterator     pos = m_TracesGroups.begin();
        CTracesGroup*                       pGroup = NULL;

        while (pos != m_TracesGroups.end() && pGroup == NULL)
        {
            if ( pos->second->Name() == name )
            {
                pGroup = pos->second;
            }

            ++ pos;
        }

        return pGroup;
    }


    /**
     *
     */
    CTracesGroup* CTracesGroupMgr::CreateTracesGroup(const QString& name)
    {
        if ( NULL != GetGroup(name) )
            return NULL;

        CTracesGroup*   pGroup = new CTracesGroup();
        pGroup->Name() = name;
        
        m_TracesGroups[pGroup->Id()] = pGroup;
        
        m_Listeners.OnNewTracesGroup(pGroup);
        
        return pGroup;
    }
    
    
    /**
     *
     */
    void CTracesGroupMgr::ReleaseTracesGroup(CTracesGroup* pTracesGroup)
    {
        m_Listeners.OnTracesGroupWillBeDeleted(pTracesGroup);
        
        m_TracesGroups.erase(pTracesGroup->Id());
        delete pTracesGroup;
    }
    
    
    
    
    /*******************************************************************
            CTracesGroupMgrNotificationsListeners
     ******************************************************************/
    
    
    /**
     *
     */
    CTracesGroupMgrNotificationsListeners::CTracesGroupMgrNotificationsListeners()
    {
        
    }
    
    
    /**
     *
     */
    CTracesGroupMgrNotificationsListeners::~CTracesGroupMgrNotificationsListeners()
    {
        
    }
    
    
    /**
     *
     */
    void CTracesGroupMgrNotificationsListeners::Add( ITracesGroupMgrNotificationsListener* pListener )
    {
        m_Listeners.push_back(pListener);
    }
    
    
    /**
     *
     */
    void CTracesGroupMgrNotificationsListeners::Remove( ITracesGroupMgrNotificationsListener* pListener )
    {
        TListenersList::iterator          pos = m_Listeners.begin();
        
        while (pos != m_Listeners.end())
        {
            
            if ( *pos == pListener )
            {
                m_Listeners.erase(pos);
                break;
            }
            
            ++ pos;
        }        
    }
    
    
    /**
     *
     */
    void CTracesGroupMgrNotificationsListeners::OnNewTracesGroup(TraceClientCore::CTracesGroup *pGroup)
    {
        TListenersList::const_iterator          pos = m_Listeners.begin();
        
        while (pos != m_Listeners.end())
        {
            (*pos)->OnNewTracesGroup(pGroup);
            
            ++ pos;
        }
    }
    
    
    /**
     *
     */
    void CTracesGroupMgrNotificationsListeners::OnTracesGroupWillBeDeleted(TraceClientCore::CTracesGroup *pGroup)
    {
        TListenersList::const_iterator          pos = m_Listeners.begin();
        
        while (pos != m_Listeners.end())
        {
            (*pos)->OnTracesGroupWillBeDeleted(pGroup);
            
            ++ pos;
        }        
    }
}

