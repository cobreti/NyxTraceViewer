#ifndef _TRACECHANNEL_HPP_
#define _TRACECHANNEL_HPP_


#include <Nyx.hpp>
#include "TraceFeeder.hpp"

#include <list>

namespace TraceClientCore
{
    class CTraceData;
    class CTracesPool;
    

    /**
     *
     */
    class CTraceChannel
    {
    public:
        CTraceChannel( CTracesPool* pPool );
        virtual ~CTraceChannel();
        
        const Nyx::CAString&        Name() const        { return m_Name; }
        Nyx::CAString&              Name()              { return m_Name; }
        
        CTracesPool*                Pool() const        { return m_pPool; }

		const CTraceFeederRef&		Feeder() const		{ return m_refFeeder; }
		CTraceFeederRef&			Feeder()			{ return m_refFeeder; }
        
        void Insert(CTraceData* pTraceData);
        void Clear();

        void Stop();
        
    protected:
        
        Nyx::CAString               m_Name;
        CTracesPool*                m_pPool;
		CTraceFeederRef				m_refFeeder;
    };
    
    
    /**
     *
     */
    class CTraceChannelListItem
    {
    public:
        CTraceChannelListItem( CTraceChannel& channel ) : m_rChannel(channel) {}
        CTraceChannelListItem(const CTraceChannelListItem& item) : m_rChannel(item.m_rChannel) {}
        ~CTraceChannelListItem() {}
        
//        CTraceChannel&      Channel()               { return m_rChannel; }
        CTraceChannel&    Channel() const     { return m_rChannel; }
        
    protected:
        CTraceChannel&      m_rChannel;
    };
    
    
    /**
     *
     */
    class CTraceChannelsList : public std::list<CTraceChannelListItem>
    {
    public:
        CTraceChannelsList() : std::list<CTraceChannelListItem>() {}
        ~CTraceChannelsList() {}
    };
}


#endif // _TRACECHANNEL_HPP_
