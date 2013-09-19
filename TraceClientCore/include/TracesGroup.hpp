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

namespace TraceClientCore
{
    
    typedef     Nyx::UInt32         TracesGroupId;
    
    /**
     *
     */
    class CTracesGroup
    {
        friend class CTracesGroupMgr;
        
    public:
        const TracesGroupId&        Id() const      { return m_Id; }
        
        const Nyx::CAString&    Name() const            { return m_Name; }
        Nyx::CAString&          Name()                  { return m_Name; }
        
    protected:
        
        CTracesGroup();
        virtual ~CTracesGroup();
        
        
    protected:
        
        TracesGroupId           m_Id;
        Nyx::CAString           m_Name;
        
    private:
        
        static TracesGroupId        s_NextAvailId;
    };
}


#endif
