//
//  TracesGroup.cpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-18.
//
//

#include "TracesGroup.hpp"


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
}