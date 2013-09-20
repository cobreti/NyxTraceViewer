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


#include <list>

namespace TraceClientCore
{
    class CTraceChannel;
    class CTracesView;
    class CMultiViewTracesIterator;
    
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
        
        void AddChannel( CTraceChannel* pChannel );
        bool HasChannel( CTraceChannel* pChannel );
        
        CMultiViewTracesIterator FirstPos();
        CMultiViewTracesIterator LastPos();
        
    protected:
        
        typedef     std::list<CTracesView*>     TTracesViews;
        
    protected:
        
        CTracesGroup();
        virtual ~CTracesGroup();
        
        
    protected:
        
        TracesGroupId           m_Id;
        Nyx::CAString           m_Name;
        TTracesViews            m_Views;
        
    private:
        
        static TracesGroupId        s_NextAvailId;
    };
}


#endif
