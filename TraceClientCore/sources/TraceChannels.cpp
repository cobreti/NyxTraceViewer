#include "TraceChannels.hpp"


namespace TraceClientCore
{
    /**
     *
     */
    CTraceChannels::CTraceChannels()
    {
        
    }
    
    
    /**
     *
     */
    CTraceChannels::~CTraceChannels()
    {
        Clear();
    }
    
    
    /**
     *
     */
    Nyx::NyxResult CTraceChannels::Add( CTraceChannel* pChannel )
    {
        TraceChannelsMap::const_iterator    pos = m_Channels.find(pChannel->Name());
        
        if ( pos != m_Channels.end() )
            return Nyx::kNyxRes_Failure;
        
        m_Channels.insert( std::make_pair(pChannel->Name(), pChannel) );
        
        return Nyx::kNyxRes_Success;
    }
    
    
    /**
     *
     */
    CTraceChannel* CTraceChannels::Get( const Nyx::CAString& name )
    {
        TraceChannelsMap::const_iterator       pos = m_Channels.find(name);
        
        if ( pos != m_Channels.end() )
            return pos->second;
        
        return NULL;
    }
    
    
    /**
     *
     */
    void CTraceChannels::Update( CTraceChannel* pChannel )
    {
        TraceChannelsMap::iterator      pos = m_Channels.begin();
        
        while ( pos != m_Channels.end() )
        {
            if ( pos->second == pChannel )
            {
                m_Channels.erase(pos);
                break;
            }
            
            ++ pos;
        }
        
        m_Channels.insert( std::make_pair(pChannel->Name(), pChannel) );
    }
    

    /**
     *
     */
    void CTraceChannels::Stop()
    {
        TraceChannelsMap::iterator  pos = m_Channels.begin();

        while ( pos != m_Channels.end() )
        {
            pos->second->Stop();
            ++ pos;
        }
    }

    
    /**
     *
     */
    void CTraceChannels::GetChannelsList( CTraceChannelsList& rList ) const
    {
        TraceChannelsMap::const_iterator        pos = m_Channels.begin();
        
        while ( pos != m_Channels.end() )
        {
            rList.push_back( CTraceChannelListItem(*pos->second) );
            ++ pos;
        }
    }
    
    
    /**
     *
     */
    void CTraceChannels::Clear()
    {
        TraceChannelsMap::iterator      pos = m_Channels.begin();
        
        while ( pos != m_Channels.end() )
        {
            delete pos->second;
            ++ pos;
        }
    }
}
