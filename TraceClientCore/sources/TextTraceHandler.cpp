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
                HandleTraceLine(szLine, pThreadPos, pSrcPos);
    			break;
    		}

    		++ pSrcPos;
    	}
    }


    /**
     *
     */
    void CTextTraceHandler::HandleTraceLine(char* szModule, char* pThread, char* szContent)
    {
    	Nyx::CTF_TickCount		TickCount;
    	Nyx::NyxSize			len = strlen(TickCount.GetAnsiText());
    	char					Buffer[30];

    	strncpy(Buffer, TickCount.GetAnsiText()+2, len-Nyx::NyxSize(4));
    	Buffer[len-Nyx::NyxSize(4)] = '\0';

    	NYXTRACE(0x0, "trace line module : '" << Nyx::CTF_AnsiText(szModule) << Nyx::CTF_AnsiText("'") );

    	if ( pThread != NULL )
    		NYXTRACE(0x0, "trace line thread : '" << Nyx::CTF_AnsiText(pThread) << Nyx::CTF_AnsiText("'") );

    	NYXTRACE(0x0, "trace tickcount : " << Nyx::CTF_AnsiText(Buffer) );

    	NYXTRACE(0x0, "trace line content : '" << Nyx::CTF_AnsiText(szContent) << Nyx::CTF_AnsiText("'") );

    	CModule&		rModule = CModule::Instance();
    	CTraceChannel*	pChannel = rModule.TraceChannels().Get( Nyx::CAString(szModule) );

    	if ( pChannel )
    	{
    		Nyx::CUtf8String	content(szContent);

    		CTraceData*		pTraceData = new (pChannel->Pool()->MemoryPool())CTraceData(pChannel->Pool()->MemoryPool());

    		if ( pThread == NULL )
    			pTraceData->ThreadId() = "default";
    		else
    			pTraceData->ThreadId() = pThread;


    		pTraceData->TickCount() = Buffer;
    		pTraceData->Data() = content;
    		pTraceData->OwnerPool() = pChannel->Pool();

    		pChannel->Insert(pTraceData);
    	}
    }
}
