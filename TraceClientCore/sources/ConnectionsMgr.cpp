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
            CTraceData*		pTraceData = new (pChannel->Pool()->MemoryPool())CTraceData(pChannel->Pool()->MemoryPool());
            pTraceData->Data() = L"Disconnection";
            pTraceData->Type() = CTraceData::eTT_ConnectionStatus_Disconnection;
            pTraceData->OwnerPool() = pChannel->Pool();

            pChannel->Pool()->Repository().InsertDisconnection(pTraceData);
            ++ pos;
        }
    }
}

