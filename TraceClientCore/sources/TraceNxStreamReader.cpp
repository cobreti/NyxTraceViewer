
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
    CTraceData* CTraceNxStreamReader::Read( NyxNet::CNxStreamReader& Reader )
    {
        CTraceData*						pTraceData = NULL;
        NyxNet::TraceFlags              flags = 0;
        Nyx::NyxResult                  res;
        Nyx::UInt32                     SectionsCount = 0;
        
        if ( Reader.Valid() )
        {
            pTraceData = new (m_pPool->MemoryPool())CTraceData(m_pPool->MemoryPool());
            
            // sections count
            {
                NyxNet::CNxSectionStreamReader      SectionReader(Reader);
                
                m_ReadBuffer.Resize(SectionReader.Size());
                res = SectionReader.Read(m_ReadBuffer, SectionReader.Size());
                if ( Nyx::Failed(res) )
                    throw Nyx::CException("failure to read sections count");
                
                SectionsCount = *m_ReadBuffer.GetBufferAs<Nyx::UInt32>();
            }
            
            // flags
            {
                NyxNet::CNxSectionStreamReader		SectionReader(Reader);
                
                m_ReadBuffer.Resize(SectionReader.Size());
                res = SectionReader.Read(m_ReadBuffer, SectionReader.Size());
                if ( Nyx::Failed(res) )
                    throw Nyx::CException("failure to read version");
                
                flags = *m_ReadBuffer.GetBufferAs<NyxNet::TraceFlags>();
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
                
                if ( flags & NyxNet::TFlags_WideChar )
                    pTraceData->Data() = m_ReadBuffer.GetBufferAs<wchar_t>();
                else if ( flags & NyxNet::TFlags_Ansi )
                    pTraceData->Data() = m_ReadBuffer.GetBufferAs<char>();
            }
                            
            pTraceData->OwnerPool() = m_pPool;
            //GetOwnerPool()->Repository().Insert(pTraceData);
        }
    
        return pTraceData;
    }
    
}