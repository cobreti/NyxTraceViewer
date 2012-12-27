#include "TcpTxtTracesReceiver.hpp"
#include "TraceChannel.hpp"
#include "TraceClientCoreModule.hpp"
#include "TcpTracesReceiversSvr.hpp"
#include "TcpTracesReceiversTable.hpp"
#include "NyxStreamRW.hpp"
#include <NyxSwap.hpp>

namespace TraceClientCore
{
    /**
     *
     */
    CTcpTxtTracesReceiver::CTcpTxtTracesReceiver(CTcpTxtTracesReceiversSvr* pSvr, NyxNet::IConnection* pConnection) :
    m_pConnection(pConnection),
    m_pServer(pSvr),
    m_pChannel(NULL)
    {
    	m_Buffer.Resize(4096);
//        CTcpTxtTracesReceiversTable::MethodsRef    refMethods = m_pServer->ReceiversTable().GetMethods();
//
//        refMethods->Insert(this);
    }
    
    
    /**
     *
     */
    CTcpTxtTracesReceiver::~CTcpTxtTracesReceiver()
    {
//        CTcpTxtTracesReceiversTable::MethodsRef    refMethods = m_pServer->ReceiversTable().GetMethods();
//
//        refMethods->Remove(this);
    }


    /**
     *
     */
    void CTcpTxtTracesReceiver::HandleStream( Nyx::IStreamRW& rStream )
    {
    	Nyx::NyxResult	res = Nyx::kNyxRes_Failure;
    	Nyx::NyxSize	readSize = 0;

    	res = rStream.Read( m_Buffer, m_Buffer.FreeSize(), readSize );

    	const char* szText = m_Buffer.GetBufferAs<const char>();

    	readSize = 0;
    }
    
    /**
     *
     */
    Nyx::NyxResult CTcpTxtTracesReceiver::OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::IConnectionHandler*& pCloneHandler )
    {
        
        return Nyx::kNyxRes_Success;
    }
    
    
    /**
     *
     */
    void CTcpTxtTracesReceiver::OnConnectionTerminated( NyxNet::IConnection* pConnection )
    {        
        delete this;
    }
}


