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
		Nyx::NyxSize	frameSize = 2;

		//::memset(m_Buffer, 0, m_Buffer.FreeSize());
		res = rStream.Read( m_Buffer.getWritePos(), m_Buffer.FreeSize(), readSize );

        if ( Nyx::Failed(res) )
        {
            NYXTRACE(0x0, "protocol rStream failure returned");
        }

		if ( Nyx::Succeeded(res) )
		{
			m_Buffer.addDataSize(readSize);

			if ( m_Buffer.DataSize() < frameSize )
				return Nyx::kNyxRes_Success;

//			char* szStr = m_Buffer.GetBufferAs<char>();

			Nyx::UInt8*		pBytes = m_Buffer.GetBufferAs<Nyx::UInt8>();
			Nyx::UInt8 		Mask[4] = {0, 0, 0, 0};

			NYXTRACE(0x0, L"new buffer input");

			//size_t			size = m_Buffer.DataSize();
			//Nyx::UInt8*		pDataBytes = pBytes;
			//while ( size > 0 )
			//{
			//	NYXTRACE(0x0, L"byte " << Nyx::CTF_Int(size) << L" --> " << Nyx::CTF_Hex(*pDataBytes));

			//	++ pDataBytes;
			//	-- size;
			//}

			bool bEndFrame = *pBytes & 0x80;
			Nyx::UInt8 opCode = *pBytes & 0x0F;

            if ( opCode == 0x09 ) // ping frame
            {
                NYXTRACE(0x0, "ping frame received");
                Nyx::UInt8  pong[4] = { 0x8A, 0, 0, 0 };
                Nyx::NyxSize    writtenSize;
                
                rStream.Write(&pong[0], sizeof(pong[0]), writtenSize);
                rStream.Write(&pong[1], sizeof(pong[0]), writtenSize);
                rStream.Write(&pong[2], sizeof(pong[0]), writtenSize);
                rStream.Write(&pong[3], sizeof(pong[0]), writtenSize);

				m_Buffer.ReadData(NULL, frameSize);
                return Nyx::kNyxRes_Success;
            }
            
			if ( opCode == 0x08 ) // closing connection
            {
                NYXTRACE(0x0, "protocol closing connection");
				return Nyx::kNyxRes_Failure;
            }

            if ( opCode & 0x01 != 0x01 )
                return Nyx::kNyxRes_Success;
            
			++ pBytes;
			++ frameSize;

			bool bMask = *pBytes & 0x80;
			Nyx::UInt32 len = *pBytes & 0x7F;
			Nyx::UInt32 headerSize = 2;


			++ pBytes;
			++ frameSize;

			if ( len == 126 )
			{
                len = *pBytes << 8;
                ++ pBytes;
				++ frameSize;
                len |= *pBytes;
                ++ pBytes;
				++ frameSize;

                headerSize += 2;
			}
			else if ( len == 127 ) // cannot handle 64 bits length for now
				return Nyx::kNyxRes_Success;

			if ( bMask )
			{
//				Nyx::UInt8 Mask[4] = { pBytes[2], pBytes[3], pBytes[4], pBytes[5] };
				for (int i = 0; i < 4; ++i)
				{
					Mask[i] = *pBytes;
					++ pBytes;
					++ frameSize;
				}

				headerSize += 4;
			}

//			Nyx::UInt8* pValues = pBytes;

//			len -= headerSize;

			char szLine[4096];

			int i = 0;
			while (i < len )
			{
				Nyx::UInt8 value = *pBytes;

				if ( bMask )
					value ^= Mask[i % 4];

//					NYXTRACE(0x0, "final value : " << Nyx::CTF_Hex(value));
				szLine[i] = value;

				++ i;
				++ pBytes;
				++ frameSize;
			}

			m_Buffer.ReadData(NULL, frameSize);

			szLine[i++] = '\0';

			NYXTRACE(0x0, "line : '" << szLine << "'");

			m_TextTraceHandler.ParseRawTraceLine(szLine, i);
		}

		return res;
	}


}

