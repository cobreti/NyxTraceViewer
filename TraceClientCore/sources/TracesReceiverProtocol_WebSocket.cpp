#include <Nyx.hpp>

#include "TracesReceiverProtocol_WebSocket.hpp"

#include <NyxStreamRW.hpp>

namespace TraceClientCore
{
	/**
	 *
	 */
	CTracesReceiverProtocol_WebSocket::CTracesReceiverProtocol_WebSocket() : CTracesReceiverProtocol()
	{
		m_Buffer.Resize(4096);
	}


	/**
	 *
	 */
	CTracesReceiverProtocol_WebSocket::~CTracesReceiverProtocol_WebSocket()
	{

	}


	/**
	 *
	 */
	Nyx::NyxResult CTracesReceiverProtocol_WebSocket::HandleStream( Nyx::IStreamRW& rStream )
	{
    	Nyx::NyxResult	res = Nyx::kNyxRes_Failure;
    	Nyx::NyxSize	readSize = 0;
    	Nyx::NyxSize	StringEndPos = 0;

		::memset(m_Buffer, 0, m_Buffer.FreeSize());
		res = rStream.Read( m_Buffer, m_Buffer.FreeSize(), readSize );

		if ( Nyx::Succeeded(res) )
		{
//			char* szStr = m_Buffer.GetBufferAs<char>();

			Nyx::UInt8*	pBytes = m_Buffer.GetBufferAs<Nyx::UInt8>();

			bool bEndFrame = pBytes[0] & 0x80;
			Nyx::UInt8 opCode = pBytes[0] & 0x0F;
			bool bMask = pBytes[1] & 0x80;
			Nyx::UInt32 len = pBytes[1] & 0x7F;

			if ( opCode & 0x8 ) // closing connection
				return Nyx::kNyxRes_Failure;

			if ( bMask )
			{
				Nyx::UInt8 Mask[4] = { pBytes[2], pBytes[3], pBytes[4], pBytes[5] };

				Nyx::UInt8* pValues = pBytes + 6;

				char szLine[4096];

				int i = 0;
				while (i < len )
				{
					Nyx::UInt8 value = pValues[i] ^ Mask[i % 4];
//					NYXTRACE(0x0, "final value : " << Nyx::CTF_Hex(value));
					szLine[i] = value;

					++ i;
				}

				szLine[i] = '\0';

				NYXTRACE(0x0, "line : '" << szLine << "'");
			}
		}

		return res;
	}


    /**
     *
     */
    void CTracesReceiverProtocol_WebSocket::HandleRawTraceLine(char* szLine, const Nyx::NyxSize& size)
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
    void CTracesReceiverProtocol_WebSocket::HandleTraceLine(char* szHeader, char* pThread, char* szContent)
    {
    	NYXTRACE(0x0, "trace line module : '" << Nyx::CTF_AnsiText(szHeader) << Nyx::CTF_AnsiText("'") );

    	if ( pThread != NULL )
    		NYXTRACE(0x0, "trace line thread : '" << Nyx::CTF_AnsiText(pThread) << Nyx::CTF_AnsiText("'") );

    	NYXTRACE(0x0, "trace line content : '" << Nyx::CTF_AnsiText(szContent) << Nyx::CTF_AnsiText("'") );
    }
}

