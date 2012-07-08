
#include "TraceNxStreamReader.hpp"
#include "TraceData.hpp"
#include "TracesPool.hpp"
#include "NyxNetTraceFlags.hpp"

#include "TraceClientCoreModule.hpp"

#include <NyxNet.hpp>


Nyx::CTraceStream& operator << ( Nyx::CTraceStream& stream, const Nyx::CTraceTimeReference& timeref )
{
    stream << L"[ (" << timeref.TimeString().c_str() << L")  ("
            << timeref.TickCount().c_str() << L") ]";

    return stream;
}



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
        Nyx::UInt32                     TimeRefInSeconds = 0;
        Nyx::UInt32                     TickCountRef = 0;
        Nyx::UInt32                     ModuleTimeRefInSeconds = 0;
        Nyx::UInt32                     ModuleTickCountRef = 0;
        
        NYXTRACE(0x0, L"client module time reference : " << CModule::Instance().TraceTimeReference());

        const Nyx::CTraceTimeReference&   rTimeRef = CModule::Instance().TraceTimeReference();

        ModuleTimeRefInSeconds = rTimeRef.Time().Hours() * 3600 + rTimeRef.Time().Minutes() * 60 + rTimeRef.Time().Seconds();
        sscanf( CModule::Instance().TraceTimeReference().TickCount().c_str(), "%lu.", &ModuleTickCountRef);

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

            // local time reference
            {
                NyxNet::CNxSectionStreamReader      SectionReader(Reader);

                m_ReadBuffer.Resize(SectionReader.Size());
                res = SectionReader.Read(m_ReadBuffer, SectionReader.Size());
                if ( Nyx::Failed(res) )
                    throw Nyx::CException("failure to read local time reference");

                //memcpy(&value, m_ReadBuffer.GetBufferAs<Nyx::UInt32>(), sizeof(value));

                //NYXTRACE(0x0, L"Trace time ref --> " << (value >> 16) << L":" << ((value >> 8) & 0xFF) << L":" << (value & 0xFF) );

                //TimeRefInSeconds = (value >> 16) * 3600 + ((value >> 8) & 0xFF) * 60 + (value & 0xFF);
            }

            // tick count reference
            {
                NyxNet::CNxSectionStreamReader		SectionReader(Reader);
                
                m_ReadBuffer.Resize(SectionReader.Size());
                res = SectionReader.Read(m_ReadBuffer, SectionReader.Size());
                if ( Nyx::Failed(res) )
                    throw Nyx::CException("failure to read tick count reference");
                
                //NYXTRACE(0x0, L"Trace tick count ref : " << m_ReadBuffer.GetBufferAs<char>());
                //pTraceData->TickCount() = m_ReadBuffer.GetBufferAs<char>();

                //sscanf( m_ReadBuffer.GetBufferAs<char>(), "%lu.", &TickCountRef );
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

            NYXTRACE(0x0, L"Time Ref in seconds : " << (int)TimeRefInSeconds << L" - tick count ref : " << (int)TickCountRef );
            NYXTRACE(0x0, L"Module time ref in seconds : " << (int)ModuleTimeRefInSeconds << L" - module tick count ref : " << (int)ModuleTickCountRef );
            NYXTRACE(0x0, L"Trace tick count : " << pTraceData->TickCount().c_str() );
            
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

