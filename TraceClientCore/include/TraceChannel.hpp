#ifndef _TRACECHANNEL_HPP_
#define _TRACECHANNEL_HPP_


#include <Nyx.hpp>
#include "TraceFeeder.hpp"
#include "TracesPool.hpp"

#include <list>
#include <set>

#include <QtCore>

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
        
        const QString&              Name() const        { return m_Name; }
        QString&                    Name()              { return m_Name; }
        
        CTracesPool*                Pool() const        { return m_refPool; }

		const CTraceFeederRef&		Feeder() const		{ return m_refFeeder; }
		CTraceFeederRef&			Feeder()			{ return m_refFeeder; }
        
        void Insert(CTraceData* pTraceData);
        void Clear();

        void Stop();
        
    protected:
        
//        Nyx::CAString               m_Name;
        QString                     m_Name;
        CTracesPoolRef              m_refPool;
		CTraceFeederRef				m_refFeeder;
    };
    

    /**
     * @brief The CTraceChannelSet class
     */
    class CTraceChannelSet : public std::set<CTraceChannel*>
    {
    public:
        CTraceChannelSet() {}
        virtual ~CTraceChannelSet() {}
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
