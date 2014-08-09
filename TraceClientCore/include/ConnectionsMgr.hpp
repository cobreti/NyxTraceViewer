#ifndef CONNECTIONMGR_HPP
#define CONNECTIONMGR_HPP

#include <Nyx.hpp>
#include <NyxNet.hpp>

#include "TraceChannel.hpp"

#include <map>


namespace TraceClientCore
{
    class CConnectionsMgr
    {
    public:
        CConnectionsMgr();
        virtual ~CConnectionsMgr();

        virtual void onNewConnection( const NyxNet::CAddress& address  );
        virtual void onCloseConnection( const NyxNet::CAddress& address, const CTraceChannelSet& channelsSet );

    protected:

        typedef     std::map<NyxNet::CAddress, Nyx::CAString>       TClientConnectionsMap;

    protected:

        TClientConnectionsMap       m_ClientsConnectionsTable;
    };
}

#endif // CONNECTIONMGR_HPP
