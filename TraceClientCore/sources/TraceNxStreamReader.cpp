
#include "TraceNxStreamReader.hpp"
#include "TraceData.hpp"
#include "TracesPool.hpp"
#include "NyxNetTraceFlags.hpp"

#include <NyxNet.hpp>

namespace TraceClientCore
{
    /**
     *
     */
    CTraceNxStreamReader::CTraceNxStreamReader( CTracesPool* pPool ) :
    m_pPool(pPool)
    {
    }
    
    
    /**
     *
     */
    CTraceNxStreamReader::~CTraceNxStreamReader()
    {
    }
    
    
    /**
     *
     */
    CTraceData* CTraceNxStreamReader::Read( Nyx::UInt32 SectionsCount, NyxNet::CNxStreamReader& Reader )
    {
        CTraceData*						pTraceData = NULL;
        NyxNet::CTraceFlags             flags;
        Nyx::NyxResult                  res;
        
        if ( Reader.Valid() )
        {
            pTraceData = new (m_pPool->MemoryPool())CTraceData(m_pPool->MemoryPool());
                        
            // flags
            {
                NyxNet::CNxSectionStreamReader		SectionReader(Reader);
                
                m_ReadBuffer.Resize(SectionReader.Size());
                res = SectionReader.Read(m_ReadBuffer, SectionReader.Size());
                if ( Nyx::Failed(res) )
                    throw Nyx::CException("failure to read version");
                
                flags = *m_ReadBuffer.GetBufferAs<NyxNet::CTraceFlags>();
                pTraceData->Flags() = flags;
            }
            
            // thread id
            {
                NyxNet::CNxSectionStreamReader		SectionReader(Reader);
                
                m_ReadBuffer.Resize(SectionReader.Size());
                res = SectionReader.Read(m_ReadBuffer, SectionReader.Size());
                if ( Nyx::Failed(res) )
                    throw Nyx::CException("failure to read thread id");
                
                pTraceData->ThreadId() = m_ReadBuffer.GetBufferAs<char>();
            }
            
            // tick count
            {
                NyxNet::CNxSectionStreamReader		SectionReader(Reader);
                
                m_ReadBuffer.Resize(SectionReader.Size());
                res = SectionReader.Read(m_ReadBuffer, SectionReader.Size());
                if ( Nyx::Failed(res) )
                    throw Nyx::CException("failure to read tick count");
                
                pTraceData->TickCount() = m_ReadBuffer.GetBufferAs<char>();
            }
            
            // data
            {
                NyxNet::CNxSectionStreamReader		SectionReader(Reader);
                
                m_ReadBuffer.Resize(SectionReader.Size());
                res = SectionReader.Read(m_ReadBuffer, SectionReader.Size());
                if ( Nyx::Failed(res) )
                    throw Nyx::CException("failure to read data");
                
                if ( flags.IsWideChar() )
                {
                    char*           pBuffer = m_ReadBuffer.GetBufferAs<char>();

                    if ( sizeof(wchar_t) < flags.WideCharSize() )
                    {
                        char*           pSrc = pBuffer;
                        char*           pDst = pBuffer;
                        Nyx::NyxSize    size = SectionReader.Size();
                        
                        while ( size > 0 )
                        {
                            memmove( pDst, pSrc, sizeof(wchar_t) );
                            pSrc += flags.WideCharSize();
                            pDst += sizeof(wchar_t);
                            size -= flags.WideCharSize();
                        }
                    }
                    else if ( sizeof(wchar_t) > flags.WideCharSize() )
                    {
                    	size_t	nChar = SectionReader.Size() / flags.WideCharSize();
                    	size_t	NewSize = nChar * sizeof(wchar_t);
                    	size_t	DiffSize = sizeof(wchar_t) - flags.WideCharSize();
                    	char*	pSrc = NULL;
                    	char*	pDst = NULL;

                    	m_ReadBuffer.Resize(NewSize);

                    	pBuffer = m_ReadBuffer.GetBufferAs<char>();
                    	pSrc = pBuffer + SectionReader.Size() - flags.WideCharSize();
                    	pDst = pBuffer + NewSize - DiffSize;

                        while ( NewSize > 0 )
                    	{
                            memset(pDst, 0, DiffSize);
                            pDst -= flags.WideCharSize();
                            memcpy(pDst, pSrc, flags.WideCharSize());
                            pDst -= DiffSize;
                            pSrc -= flags.WideCharSize();
                            NewSize -= sizeof(wchar_t);
                    	}
                    }

                    pTraceData->Data() = (wchar_t*)pBuffer;
                }
                else if ( flags.IsAnsi() )
                {
                    pTraceData->Data() = m_ReadBuffer.GetBufferAs<char>();
                }
            }
                            
            pTraceData->OwnerPool() = m_pPool;
        }
    
        return pTraceData;
    }
    
}

