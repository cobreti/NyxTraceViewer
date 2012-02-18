#ifndef _TRACECHANNELS_HPP_
#define _TRACECHANNELS_HPP_

#include "TraceChannel.hpp"

#include <map>

namespace TraceClientCore
{
    /**
     *
     */
    class CTraceChannels
    {
    public:
        CTraceChannels();
        virtual ~CTraceChannels();
        
        virtual Nyx::NyxResult Add( CTraceChannel* pChannel );
        virtual CTraceChannel* Get( const Nyx::CAString& name );
        virtual void Update( CTraceChannel* pChannel );
        virtual void Stop();
        
        virtual void GetChannelsList( CTraceChannelsList& rList ) const;
        
    protected:
        
        typedef     std::map<Nyx::CAString, CTraceChannel*>        TraceChannelsMap;
        
    protected:
        
        void Clear();
        
    protected:
        
        TraceChannelsMap        m_Channels;
    };
}


#endif // _TRACECHANNELS_HPP_
