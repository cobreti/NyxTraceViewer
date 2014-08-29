#include "TcpTxtTracesReceiver.hpp"
#include "TraceChannel.hpp"
#include "TraceClientCoreModule.hpp"
#include "TcpTxtTracesReceiversSvr.hpp"
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

#include <QFile>
#include <QTextStream>

namespace TraceClientCore
{
	char *base64(const unsigned char *input, int length)
	{
	  BIO *bmem, *b64;
	  BUF_MEM *bptr;

	  b64 = BIO_new(BIO_f_base64());
	  bmem = BIO_new(BIO_s_mem());
	  b64 = BIO_push(b64, bmem);

		bool done = false;
		int res = 0;
		while(!done)
		{
			res = BIO_write(b64, input, length);

			if(res <= 0) // if failed
			{
				if(BIO_should_retry(b64)){
					continue;
				}
				else // encoding failed
				{
					/* Handle Error!!! */
				}
			}
			else // success!
				done = true;
		}

		BIO_flush(b64);

		// get a pointer to mem's data
		char* dt;
		long len = BIO_get_mem_data(bmem, &dt);

		char* buff = (char*)malloc(len);
		memcpy(buff, dt, len-1);
		buff[len-1] = 0;

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

    
    class CHttpHandlerCB : public Nyx::CRefCount_Impl<NyxWebSvr::CHttpHandler>
    {
    public:
        CHttpHandlerCB( CTcpTxtTracesReceiver& rReceiver ) : m_rReceiver(rReceiver) {}
        
        virtual void OnGetRequest( NyxWebSvr::CConnHttpHandler& rConnHttpHandler, char* szPath, char* szParams )
        {
            m_rReceiver.OnGetRequest_Trace(rConnHttpHandler, szPath, szParams);
        }
        
        virtual void OnPostRequest( NyxWebSvr::CConnHttpHandler& rConnHttpHandler, char* szPath, char* szParams )
        {
            m_rReceiver.OnPostRequest_Trace(rConnHttpHandler, szPath, szParams);
        }
        
    protected:
        
        CTcpTxtTracesReceiver&  m_rReceiver;
    };
    
    
	/**
     *
     */
    CTcpTxtTracesReceiver::CTcpTxtTracesReceiver(CTcpTxtTracesReceiversSvr* pSvr, NyxNet::IConnection* pConnection) :
    m_pConnection(pConnection),
    m_pServer(pSvr),
    m_pProtocol(NULL)
    {
    	m_Buffer.Resize(1024 * 1024);

        GetClientAddress(pConnection);
        
        TraceClientCore::CModule::Instance().ConnectionsMgr().onNewConnection(m_ClientAddress);

        m_refHttpConnHandler = NyxWebSvr::CConnHttpHandler::Alloc();
        m_refHttpConnHandler->Handlers()->Set("/Trace", new CHttpHandlerCB(*this));
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

                if ( Nyx::Failed(res) )
                {
                    NYXTRACE(0x0, "protocol failure return");
                }
            }
    		else
    		{
                ::memset(m_Buffer.getWritePos(), 0, m_Buffer.FreeSize());
				res = rStream.Read( m_Buffer.getWritePos(), m_Buffer.FreeSize(), readSize );
                
                if ( Nyx::Failed(res) )
                {
                    NYXTRACE(0x0, "rStream failure return");
                }

				if ( Nyx::Succeeded(res) && readSize > 0 )
				{
					char* szStr = m_Buffer.GetBufferAs<char>();

                    if ( NULL != strstr(szStr, "\n") )
                    {
                        if (  NULL != strstr(szStr, "Upgrade: websocket") && NULL != strstr(szStr, "HTTP/") )
                        {
                            NYXTRACE(0x0, szStr);
                            SendWebSocketAnswer(szStr, rStream);
                            continue;
                        }
                        else if ( NULL != strstr(szStr, "GET") && NULL != strstr(szStr, "HTTP/") )
                        {
                            NYXTRACE(0x0, szStr)
//                            SendHttpAnswer(szStr, rStream);
                            m_refHttpConnHandler->HandleStream(szStr, rStream);
                            return;
                        }
                        else if ( NULL != strstr(szStr, "POST") && NULL != strstr(szStr, "HTTP/") )
                        {
                            //                            SendHttpAnswer(szStr, rStream);
//                            m_refHttpConnHandler->HandleStream(szStr, rStream);
                            return;
                        }
                    }
                    
                    m_Buffer.addDataSize(readSize);
				}
                else if ( m_pProtocol == NULL )
                {
                    res = Nyx::kNyxRes_Failure;
                }

				if ( Nyx::Succeeded(res) && m_Buffer.DataSize() > 0 )
				{
					char* szText = m_Buffer.GetBufferAs<char>();
                    
                    if ( NULL != strstr(szText, "\0") )
                    {
                        char* pChar = szText;
                        StringEndPos = 0;

                        while ( StringEndPos < m_Buffer.DataSize() )
                        {
                            if ( *pChar == '\0' )
                            {
                                m_TextTraceHandler.ParseRawTraceLine(szText, StringEndPos + Nyx::NyxSize(1));
    //							HandleRawTraceLine(szText, StringEndPos + Nyx::NyxSize(1));

                                m_Buffer.ReadData(NULL, StringEndPos + Nyx::NyxSize(1));
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

				}
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

        TraceClientCore::CModule::Instance().ConnectionsMgr().onCloseConnection(m_ClientAddress, m_TextTraceHandler.channelsSet());

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
    void CTcpTxtTracesReceiver::CloseConnection( NyxNet::IConnection* pConnection )
    {
        
    }

    
    /**
     *
     */
    void CTcpTxtTracesReceiver::OnGetRequest_Trace( NyxWebSvr::CConnHttpHandler& rConnHttpHandler, char* szPath, char* szParams )
    {
        char    szCode[16000];
        char    szPort[20];
    
        QFile   file("webContent.html");
        QString content;

        if ( file.exists() )
        {
            file.open(QIODevice::Text | QIODevice::ReadOnly);

            QTextStream in(&file);
            content = in.readAll();

            file.close();
        }
        else
        {
            file.open(QIODevice::Text | QIODevice::WriteOnly);
            file.close();
        }

        rConnHttpHandler.Write( (char*)"text/javascript", content.toStdString().c_str(), content.length() );
    }

    
    /**
     *
     */
    void CTcpTxtTracesReceiver::OnPostRequest_Trace( NyxWebSvr::CConnHttpHandler& rConnHttpHandler, char* szPath, char* szParams )
    {
        char* szMsg = strstr(szParams, "\r\n\r\n") + 4;

        m_TextTraceHandler.ParseRawTraceLine(szMsg, strlen(szMsg));
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
//    	NYXTRACE(0x0, "trace line module : '" << Nyx::CTF_AnsiText(szHeader) << Nyx::CTF_AnsiText("'") );
//
//    	if ( pThread != NULL )
//    		NYXTRACE(0x0, "trace line thread : '" << Nyx::CTF_AnsiText(pThread) << Nyx::CTF_AnsiText("'") );
//
//    	NYXTRACE(0x0, "trace line content : '" << Nyx::CTF_AnsiText(szContent) << Nyx::CTF_AnsiText("'") );
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

        strcat(szResponseContent, "HTTP/1.1 101 Web Socket Protocol Handshake\r\n");
    	strcat(szResponseContent, "Upgrade: WebSocket\r\n");
    	strcat(szResponseContent, "Connection: Upgrade\r\n");

    	strcat(szResponseContent, "Sec-WebSocket-Accept: ");
    	strcat(szResponseContent, base64output);
    	strcat(szResponseContent, "\r\n");

    	strcat(szResponseContent, "\r\n");

    	::free(base64output);

    	NYXTRACE(0x0, szResponseContent);

    	rStream.Write(szResponseContent, strlen(szResponseContent), sizeWritten);

    	if ( m_pProtocol )
    		delete m_pProtocol;

    	m_pProtocol = new CTracesReceiverProtocol_WebSocket();
    }
    
    
    /**
     *
     */
    void CTcpTxtTracesReceiver::SendHttpAnswer(char* szInHeader, Nyx::IStreamRW& rStream)
    {
        Nyx::CAString content;
        Nyx::CAString header;
        Nyx::NyxSize writtenSize = 0;
        
        header =    "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=utf-8\r\n"
        //                    "set-Cookie: test;\r\n"
        "Content-Length: 82\r\n\r\n";
        //                "Server: NyxWebServer\n";
        
        content =   "<html>\r\n"
        "<title>WebTraceSvr</title>\r\n"
        "<body>"
        "<h1>Web Trace Server</h1>\r\n"
        "</body>\r\n"
        "</html>\r\n";

        rStream.Write(header.BufferPtr(), header.length(), writtenSize);
        rStream.Write(content.BufferPtr(), content.length(), writtenSize );
    }


    void CTcpTxtTracesReceiver::GetClientAddress(NyxNet::IConnection *pConnection)
    {
        NyxNet::CSocketRef refSocket = pConnection->Socket();
        if ( !refSocket.Valid() )
            return;

        NyxNet::CTcpIpSocketRef refTcpIpSocket = refSocket->TcpIpSocket();
        if ( !refTcpIpSocket.Valid() )
            return;

        m_ClientAddress = refTcpIpSocket->ClientAddress();

    }
}


