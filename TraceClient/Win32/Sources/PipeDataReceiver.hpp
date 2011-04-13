#ifndef _PIPEDATARECEIVER_HPP_
#define _PIPEDATARECEIVER_HPP_

#include <Nyx.hpp>
#include <NyxNet.hpp>


class CPipeTraceFeeder;


/**
 *
 */
class CPipeDataReceiver : public NyxNet::INxConnectionHandler
{
public: // public methods
	CPipeDataReceiver(CPipeTraceFeeder& rFeeder);
	virtual ~CPipeDataReceiver();


	virtual void HandleStream( NyxNet::INxStreamRW& rStream );
	virtual Nyx::NyxResult OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler );
	virtual void OnConnectionTerminated( NyxNet::IConnection* pConnection );

protected: // protected members

	CPipeTraceFeeder&				m_rFeeder;

	Nyx::TBuffer<Nyx::Byte>			m_ReadBuffer;
};


#endif // _PIPEDATARECEIVER_HPP_
