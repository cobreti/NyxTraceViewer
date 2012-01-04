#ifndef _TRACEPIPERECEIVER_HPP_
#define _TRACEPIPERECEIVER_HPP_

#include <Nyx.hpp>
#include <NyxNet.hpp>


/**
 *
 */
class CTracePipeReceiver : public NyxNet::INxConnectionHandler
{
public:
    CTracePipeReceiver(const char* szPipeName);
    virtual ~CTracePipeReceiver();

    virtual void Start();
    virtual void Stop();
    
    //
    // INxConnectionHandler methods
    //
    
    virtual void HandleStream( NyxNet::INxStreamRW& rStream );
    virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler );
    virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection );

protected:
    
    virtual NyxNet::NxDataSize ReadSection( NyxNet::CNxStreamReader& Reader );
    
protected:
    
    Nyx::CAString                   m_PipeName;
    Nyx::TBuffer<Nyx::Byte>         m_Buffer;
    
    NyxNet::CNxConnectionRef        m_refNxConnection;
    NyxNet::CPipeServerRef          m_refPipeServer;
    
    NyxNet::CNxConnectionRef        m_refOutConnection;
    NyxNet::CTcpIpSocketRef         m_refOutSocket;
};


#endif // _TRACEPIPERECEIVER_HPP_
