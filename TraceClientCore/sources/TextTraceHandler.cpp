#include "TextTraceHandler.hpp"
#include "TraceChannel.hpp"
#include "TraceClientCoreModule.hpp"
#include "TraceData.hpp"
#include "TracesPool.hpp"

#include <NyxUtf8String.hpp>

namespace TraceClientCore
{
	/**
	 *
	 */
	CTextTraceHandler::CTextTraceHandler()
	{

	}


	/**
	 *
	 */
	CTextTraceHandler::~CTextTraceHandler()
	{

	}

    /**
     *
     */
    void CTextTraceHandler::ParseRawTraceLine(char* szLine, const Nyx::NyxSize& size)
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
//                HandleTraceLine(szLine, pThreadPos, pSrcPos);
                ProcessMultipleLinesContent(szLine, pThreadPos, pSrcPos);
    			break;
    		}

    		++ pSrcPos;
    	}
    }


    void CTextTraceHandler::ProcessMultipleLinesContent(char* szModule, char* pThread, char* szContent)
    {
        char*       pStart = szContent;
        char*       pNext = pStart;
        int         level = 0;

        while ( *pNext != '\0')
        {
            if ( *pNext == '\n' )
            {
                *pNext = '\0';

                if ( pNext - pStart > 0 )
                {
                    HandleTraceLine(szModule, pThread, pStart, level);
                    ++ level;
                }

                pStart = pNext+1;
            }

            ++ pNext;
        }

        if ( pNext - pStart > 0 )
        {
            HandleTraceLine(szModule, pThread, pStart, level);
        }
    }

    /**
     *
     */
    void CTextTraceHandler::HandleTraceLine(char* szModule, char* pThread, char* szContent, int level)
    {
    	Nyx::CTF_TickCount		TickCount;
    	Nyx::NyxSize			len = strlen(TickCount.GetAnsiText());
    	char					Buffer[30];

    	strncpy(Buffer, TickCount.GetAnsiText()+2, len-Nyx::NyxSize(4));
    	Buffer[len-Nyx::NyxSize(4)] = '\0';

//    	NYXTRACE(0x0, "trace line module : '" << Nyx::CTF_AnsiText(szModule) << Nyx::CTF_AnsiText("'") );

//    	if ( pThread != NULL )
//    		NYXTRACE(0x0, "trace line thread : '" << Nyx::CTF_AnsiText(pThread) << Nyx::CTF_AnsiText("'") );

//    	NYXTRACE(0x0, "trace tickcount : " << Nyx::CTF_AnsiText(Buffer) );

//    	NYXTRACE(0x0, "trace line content : '" << Nyx::CTF_AnsiText(szContent) << Nyx::CTF_AnsiText("'") );

    	CModule&		rModule = CModule::Instance();
        CTraceChannel*	pChannel = rModule.TraceChannels().Get( QString(szModule), true );

        if ( !pChannel )
        {
            NYXTRACE(0x0, L"received trace from new channel : " << Nyx::CTF_AnsiText(szModule));
        }
        
    	if ( pChannel )
    	{
            m_ChannelsSet.insert(pChannel);

//    		Nyx::CUtf8String	content(szContent);

            CTraceData*		pTraceData = new CTraceData();

            if ( level == 0 )
            {
                if ( pThread == NULL )
                    pTraceData->ThreadId() = "default";
                else
                    pTraceData->ThreadId() = pThread;


                pTraceData->TickCount() = Buffer;
            }
            else
            {
                pTraceData->ThreadId() = "";
                pTraceData->TickCount() = "";
            }

            pTraceData->Data() = szContent;
            pTraceData->Level() = level;

            QString& contentData = pTraceData->Data();

            for (size_t index = 0; index < pTraceData->Data().length(); ++index)
            {
                QChar c = contentData.at(index);

                if ( c < 32 && c != '\n' )
                {
                    contentData = contentData.replace(index, 1, QChar(32));
                }
//                if ( pTraceData->Data()[index] < 32 && pTraceData->Data()[index] != '\n' )
//                    pTraceData->Data()[index] = 32;
            }

    		pChannel->Insert(pTraceData);
    	}
    }
}
