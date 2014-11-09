#include "ConnectionsMgr.hpp"


namespace TraceClientCore
{
    CConnectionsMgr::CConnectionsMgr()
    {

    }


    CConnectionsMgr::~CConnectionsMgr()
    {

    }


    void CConnectionsMgr::onNewConnection( const NyxNet::CAddress& address )
    {
    }


    void CConnectionsMgr::onCloseConnection(const NyxNet::CAddress& address, const CTraceChannelSet& channelsSet)
    {
        CTraceChannelSet::const_iterator    pos = channelsSet.begin();

        while ( pos != channelsSet.end() )
        {
            CTraceChannel* pChannel = *pos;
            CTraceData*		pTraceData = new CTraceData();
            pTraceData->Data() = "Disconnection";
            pTraceData->Type() = CTraceData::eTT_ConnectionStatus_Disconnection;

            pChannel->Pool()->Repository().InsertDisconnection(pTraceData);
            ++ pos;
        }
    }
}

