#ifndef _TRACESRECEIVERPROTOCOL_WEBSOCKET_HPP_
#define _TRACESRECEIVERPROTOCOL_WEBSOCKET_HPP_

#include "TracesReceiverProtocol.hpp"
#include "TextTraceHandler.hpp"

namespace TraceClientCore
{
	/**
	 *
	 */
	class CTracesReceiverProtocol_WebSocket : public CTracesReceiverProtocol
	{
	public:
		CTracesReceiverProtocol_WebSocket();
		virtual ~CTracesReceiverProtocol_WebSocket();

		virtual Nyx::NyxResult HandleStream( Nyx::IStreamRW& rStream );

//    protected:
//
//		virtual void HandleRawTraceLine(char* szLine, const Nyx::NyxSize& size);
//		virtual void HandleTraceLine(char* szHeader, char* pThread, char* szContent);

    protected:
        Nyx::TBuffer<Nyx::Byte>         m_Buffer;
        CTextTraceHandler				m_TextTraceHandler;
	};
}


#endif // _TRACESRECEIVERPROTOCOL_WEBSOCKET_HPP_
