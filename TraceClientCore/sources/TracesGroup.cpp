//
//  TracesGroup.cpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-18.
//
//

#include "TracesGroup.hpp"
#include "TracesView.hpp"
#include "TraceChannel.hpp"
#include "TracesPool.hpp"

namespace TraceClientCore
{
    TracesGroupId   CTracesGroup::s_NextAvailId = 1;
    
    
    /**
     *
     */
    CTracesGroup::CTracesGroup() :
    m_Id( CTracesGroup::s_NextAvailId ++ )
    {
        
    }
    
    
    /**
     *
     */
    CTracesGroup::~CTracesGroup()
    {
        
    }
    
    
    /**
     *
     */
    void CTracesGroup::AddChannel( CTraceChannel* pChannel )
    {
        CTracesView*            pView = new CTracesView(pChannel);

        m_Views.push_back(pView);
    }
    
    
    /**
     *
     */
    bool CTracesGroup::HasChannel( CTraceChannel* pChannel )
    {
        TTracesViews::const_iterator        pos = m_Views.begin();
        
        while (pos != m_Views.end())
        {
            if ( pChannel == (*pos)->Channel() )
                return true;
            
            ++ pos;
        }
        
        return false;
    }
}
