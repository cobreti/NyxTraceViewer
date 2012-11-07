#include "TcpTracesReceiver.hpp"
#include "TraceChannel.hpp"
#include "TraceClientCoreModule.hpp"
#include "TraceNxStreamReader.hpp"
#include "TcpTracesReceivers.hpp"
#include "TcpTracesReceiversTable.hpp"

namespace TraceClientCore
{
    /**
     *
     */
    CTcpTracesReceiver::CTcpTracesReceiver(CTcpTracesReceivers* pSvr, NyxNet::IConnection* pConnection) :
    m_pConnection(pConnection),
    m_pServer(pSvr),
    m_pChannel(NULL)
    {
        CTcpTracesReceiversTable::MethodsRef    refMethods = m_pServer->ReceiversTable().GetMethods();
        
        refMethods->Insert(this);
    }
    
    
    /**
     *
     */
    CTcpTracesReceiver::~CTcpTracesReceiver()
    {
        CTcpTracesReceiversTable::MethodsRef    refMethods = m_pServer->ReceiversTable().GetMethods();
        
        refMethods->Remove(this);
    }
    
    
    /**
     *
     */
    void CTcpTracesReceiver::HandleStream( NyxNet::INxStreamRW& rStream )
    {
        NyxNet::CNxStreamReader     Reader(rStream);
        NyxNet::NxDataSize          TotalSize = 0;
        Nyx::UInt32                 SectionsCount = 0;
        Nyx::CAString               Name;
        
        if ( !Reader.Valid() )
            return;

        try
        {
            // read sections count
            {
                NyxNet::CNxSectionStreamReader        SectionReader(Reader);
                
                m_Buffer.Resize(SectionReader.Size());
                SectionReader.Read(m_Buffer, SectionReader.Size());
                
                SectionsCount = *m_Buffer.GetBufferAs<Nyx::UInt32>();            
            }
            
            // read module name
            {
                NyxNet::CNxSectionStreamReader      SectionReader(Reader);
                
                m_Buffer.Resize(SectionReader.Size());
                SectionReader.Read(m_Buffer, SectionReader.Size());
                
                Name = m_Buffer.GetBufferAs<const char>();
            }
            
            CModule&            rModule = CModule::Instance();
            CTraceChannel*      pChannel = rModule.TraceChannels().Get(Name);
            
            -- SectionsCount;
            
            if ( pChannel )
            {
                m_pChannel = pChannel;
                
                CTraceNxStreamReader        TraceReader( pChannel->Pool() );
                CTraceData*                 pTrace = NULL;
                
                pTrace = TraceReader.Read(SectionsCount, Reader);
                if ( pTrace )
                    pChannel->Insert(pTrace);
            }
            else
            {            
                while ( SectionsCount -- > 0 )
                {
                    NyxNet::CNxSectionStreamReader        SectionReader(Reader);
                    
                    m_Buffer.Resize(SectionReader.Size());
                    SectionReader.Read(m_Buffer, SectionReader.Size());
                    TotalSize += SectionReader.Size();
                }
            }
        }
        catch (...)
        {
            Nyx::CTraceStream(0x0).Write("Error reading from pipe");
        }
        
//        Nyx::CTraceStream(0x0).Write(L"Read %i data", TotalSize);
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

