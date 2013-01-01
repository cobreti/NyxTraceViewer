#include "TcpTxtTracesReceiver.hpp"
#include "TraceChannel.hpp"
#include "TraceClientCoreModule.hpp"
#include "TcpTracesReceiversSvr.hpp"
#include "TcpTracesReceiversTable.hpp"
#include "NyxStreamRW.hpp"
#include "NyxSwap.hpp"
#include <NyxSwap.hpp>
#include "TracesReceiverProtocol_WebSocket.hpp"

#include "openssl/sha.h"
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

#include <stdio.h>
#include <stdlib.h>

namespace TraceClientCore
{
	char *base64(const unsigned char *input, int length)
	{
	  BIO *bmem, *b64;
	  BUF_MEM *bptr;

	  b64 = BIO_new(BIO_f_base64());
	  bmem = BIO_new(BIO_s_mem());
	  b64 = BIO_push(b64, bmem);
	  BIO_write(b64, input, length);
	  BIO_flush(b64);
	  BIO_get_mem_ptr(b64, &bptr);

	  char *buff = (char *)malloc(bptr->length);
	  memcpy(buff, bptr->data, bptr->length-1);
	  buff[bptr->length-1] = 0;

	  BIO_free_all(b64);

	  return buff;
	}

	char *decode64(unsigned char *input, int length)
	{
	  BIO *b64, *bmem;

	  char *buffer = (char *)malloc(length);
	  memset(buffer, 0, length);

	  b64 = BIO_new(BIO_f_base64());
	  bmem = BIO_new_mem_buf(input, length);
	  bmem = BIO_push(b64, bmem);

	  BIO_read(bmem, buffer, length);

	  BIO_free_all(bmem);

	  return buffer;
	}

	/**
     *
     */
    CTcpTxtTracesReceiver::CTcpTxtTracesReceiver(CTcpTxtTracesReceiversSvr* pSvr, NyxNet::IConnection* pConnection) :
    m_pConnection(pConnection),
    m_pServer(pSvr),
    m_pChannel(NULL),
    m_bWebSocketConnected(false),
    m_pProtocol(NULL)
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
    	Nyx::NyxSize	StringEndPos = 0;

    	do
    	{
    		if ( m_pProtocol )
    		{
    			res = m_pProtocol->HandleStream(rStream);
    		}
    		else
    		{
				::memset(m_Buffer, 0, m_Buffer.FreeSize());
				res = rStream.Read( m_Buffer, m_Buffer.FreeSize(), readSize );

				if ( Nyx::Succeeded(res) )
				{
					char* szStr = m_Buffer.GetBufferAs<char>();
//
//					for (int i = 0; i < readSize; ++i)
//					{
//						int v  = szStr[i];
//						NYXTRACE(0x0, Nyx::CTF_Hex(v) );
//					}

					if (  NULL != strstr(szStr, "Upgrade: websocket") && NULL != strstr(szStr, "HTTP/") )
					{
						NYXTRACE(0x0, szStr);
						SendWebSocketAnswer(szStr, rStream);
						continue;
					}
//					else if ( m_bWebSocketConnected )
//					{
//						Nyx::UInt8*	pBytes = m_Buffer.GetBufferAs<Nyx::UInt8>();
//
//						bool bEndFrame = pBytes[0] & 0x1;
//						bool bMask = pBytes[1] & 0x80;
//						Nyx::UInt32 len = pBytes[1] & 0x7F;
//
//						if ( bMask )
//						{
//							Nyx::UInt8 Mask[4] = { pBytes[2], pBytes[3], pBytes[4], pBytes[5] };
//
//							Nyx::UInt8* pValues = pBytes + 6;
//
//							char szLine[4096];
//
//							int i = 0;
//							while (i < len )
//							{
//								Nyx::UInt8 value = pValues[i] ^ Mask[i % 4];
//								NYXTRACE(0x0, "final value : " << Nyx::CTF_Hex(value));
//								szLine[i] = value;
//
//								++ i;
//							}
//
//							szLine[i] = '\0';
//
//							NYXTRACE(0x0, "line : '" << szLine << "'");
//						}
//
//						continue;
//					}

					m_Buffer.addDataSize(readSize);
				}

				if ( Nyx::Succeeded(res) && m_Buffer.DataSize() > 0 )
				{
					char* szText = m_Buffer.GetBufferAs<char>();
					char* pChar = szText;
					StringEndPos = 0;

					while ( StringEndPos < m_Buffer.DataSize() )
					{
						if ( *pChar == '\0' )
						{
							HandleRawTraceLine(szText, StringEndPos+1);

							m_Buffer.ReadData(NULL, StringEndPos+1);
							szText = m_Buffer.GetBufferAs<char>();
							pChar = szText;
							StringEndPos = 0;
						}
						else
						{
							++ pChar;
							++ StringEndPos;
						}
					}

				}

//				readSize = 0;
    		}
    	}
    	while ( res == Nyx::kNyxRes_Success );
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
    	NYXTRACE(0x0, "Txt Traces Receiver connection terminated");

    	if ( m_pProtocol )
    	{
    		delete m_pProtocol;
    		m_pProtocol = NULL;
    	}

        delete this;
    }


    /**
     *
     */
    void CTcpTxtTracesReceiver::HandleRawTraceLine(char* szLine, const Nyx::NyxSize& size)
    {
    	char*	pSrcPos = szLine;
        char*   pThreadPos = NULL;

    	while ( *pSrcPos != '\0' )
    	{
            if ( *pSrcPos == ',' )
            {
            	if ( pThreadPos == NULL )
            		pThreadPos = pSrcPos+1;

                *pSrcPos = '\0';
            }
            else if ( *pSrcPos == '/' )
    		{
    			*pSrcPos = '\0';
    			++ pSrcPos;
                HandleTraceLine(szLine, pThreadPos, pSrcPos);
    			break;
    		}

    		++ pSrcPos;
    	}
    }


    /**
     *
     */
    void CTcpTxtTracesReceiver::HandleTraceLine(char* szHeader, char* pThread, char* szContent)
    {
    	NYXTRACE(0x0, "trace line module : '" << Nyx::CTF_AnsiText(szHeader) << Nyx::CTF_AnsiText("'") );

    	if ( pThread != NULL )
    		NYXTRACE(0x0, "trace line thread : '" << Nyx::CTF_AnsiText(pThread) << Nyx::CTF_AnsiText("'") );

    	NYXTRACE(0x0, "trace line content : '" << Nyx::CTF_AnsiText(szContent) << Nyx::CTF_AnsiText("'") );
    }


    /**
     *
     */
    void CTcpTxtTracesReceiver::SendWebSocketAnswer(char* szInHeader, Nyx::IStreamRW& rStream)
    {
    	char szResponse[2048] = "\0";
    	char szResponseContent[2048] = "\0";

    	char* szHost = strstr(szInHeader, "Host:");
    	char* szWebSocketKey = strstr(szInHeader, "Sec-WebSocket-Key:");
    	char* szOrigin = strstr(szInHeader, "Origin:");
    	char* szHostEnd = strchr(szHost, '\r');
    	*szHostEnd = '\0';

    	char* szWebSocketKeyEnd = strchr(szWebSocketKey, '\r');
    	*szWebSocketKeyEnd = '\0';

    	char* szOriginEnd = strchr(szOrigin, '\r');
    	*szOriginEnd = '\0';

    	Nyx::NyxSize		sizeWritten = 0;

    	szHost += strlen("Host:");
    	szWebSocketKey += strlen("Sec-WebSocket-Key: ");


    	unsigned char inbuf[1024] = "\0"; //"nUYteBM0xuBjUXQ6VHvhvA==";
    	unsigned char outbuf[1024] = "\0";

    	strcpy((char*)inbuf, szWebSocketKey);
    	strcat((char*)inbuf, "258EAFA5-E914-47DA-95CA-C5AB0DC85B11");

    	SHA1(inbuf, strlen((char*)inbuf), outbuf);

    	char* base64output = base64(outbuf, strlen((char*)outbuf));



//        strcat(szResponse, "HTTP/1.1 200 OK\n");
//        strcat(szResponse, "Date: Thu, 19 Feb 2009 12:27:04 GMT\n");
//        strcat(szResponse, "Server: Apache/2.2.3\n");
//        strcat(szResponse, "ETag: \"56d-9989200-1132c580\"\n");
//        strcat(szResponse, "Content-Type: text/plain\n");
//        strcat(szResponse, "Content-Length: 0\n");
//        strcat(szResponse, "Accept-Ranges: bytes\n");
//        strcat(szResponse, "Connection: open\n");
//        strcat(szResponse, "\n");
//
//        rStream.Write(reply, strlen(reply), sizeWritten);


        strcat(szResponseContent, "HTTP/1.1 101 Web Socket Protocol Handshake\r\n");
    	strcat(szResponseContent, "Upgrade: WebSocket\r\n");
    	strcat(szResponseContent, "Connection: Upgrade\r\n");

    	strcat(szResponseContent, "Sec-WebSocket-Accept: ");
    	strcat(szResponseContent, base64output);
    	strcat(szResponseContent, "\r\n");

//    	strcat(szResponseContent, "Access-Control-Allow-Headers: content-type\r\n");
//    	strcat(szResponseContent, "Access-Control-Allow-Origin: null\r\n");
//    	strcat(szResponseContent, "Access-Control-Allow-Credentials: true\r\n");
//    	strcat(szResponseContent, "Server: NyxTraceViewer\n");
//        strcat(szResponseContent, "Date: Sat, 29 Dec 2012 21:32:58 GMT\n");
    	strcat(szResponseContent, "\r\n");

//    	char responseLen[100];
//    	sprintf(responseLen, "%i", strlen(szResponseContent));
//
//    	strcpy(szResponse, "");
//        strcat(szResponse, "HTTP/1.1 200 OK\n");
//        strcat(szResponse, "Date: Thu, 19 Feb 2009 12:27:04 GMT\n");
//		strcat(szResponse, "Content-Length: ");
//		strcat(szResponse, responseLen);
//		strcat(szResponse, "\n\n");
//        strcat(szResponse, szResponseContent);
////        strcat(szResponse, "Sec-WebSocket-Version: 13\n");
////        strcat(szResponse, "Sec-WebSocket-Extensions: x-webkit-deflate-frame\n");
//        strcat(szResponse, "\n");

    	::free(base64output);

    	NYXTRACE(0x0, szResponseContent);

    	rStream.Write(szResponseContent, strlen(szResponseContent), sizeWritten);
    	m_bWebSocketConnected = true;

    	if ( m_pProtocol )
    		delete m_pProtocol;

    	m_pProtocol = new CTracesReceiverProtocol_WebSocket();
    }

}


