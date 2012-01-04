#include "TcpTracesReceiver.hpp"


namespace TraceClientCore
{
    /**
     *
     */
    CTcpTracesReceiver::CTcpTracesReceiver(NyxNet::IConnection* pConnection) :
    m_pConnection(pConnection)
    {
        
    }
    
    
    /**
     *
     */
    CTcpTracesReceiver::~CTcpTracesReceiver()
    {
        
    }
    
    
    /**
     *
     */
    void CTcpTracesReceiver::HandleStream( NyxNet::INxStreamRW& rStream )
    {
        NyxNet::CNxStreamReader     Reader(rStream);
        NyxNet::NxDataSize          TotalSize = 0;
        Nyx::UInt32                 SectionsCount = 0;
        
        try
        {
            // read sections count
            {
                NyxNet::CNxSectionStreamReader        SectionReader(Reader);
                
                m_Buffer.Resize(SectionReader.Size());
                SectionReader.Read(m_Buffer, SectionReader.Size());
                
                SectionsCount = *m_Buffer.GetBufferAs<Nyx::UInt32>();            
            }
            
            while ( SectionsCount -- > 0 )
            {
                NyxNet::CNxSectionStreamReader        SectionReader(Reader);
                
                m_Buffer.Resize(SectionReader.Size());
                SectionReader.Read(m_Buffer, SectionReader.Size());
                TotalSize += SectionReader.Size();
                
            }
            
            //        TotalSize += ReadSection(Reader); // thread id
            //        TotalSize += ReadSection(Reader); // tickcount
            //        TotalSize += ReadSection(Reader); // data
        }
        catch (...)
        {
            Nyx::CTraceStream(0x0).Write("Error reading from pipe");
        }
        
        Nyx::CTraceStream(0x0).Write(L"Read %i data", TotalSize);
    }
    
    
    /**
     *
     */
    Nyx::NyxResult CTcpTracesReceiver::OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler )
    {
        
        return Nyx::kNyxRes_Success;
    }
    
    
    /**
     *
     */
    void CTcpTracesReceiver::OnConnectionTerminated( NyxNet::IConnection* pConnection )
    {
        delete this;
    }
}

