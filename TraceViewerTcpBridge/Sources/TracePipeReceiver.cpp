#include "TracePipeReceiver.hpp"

/**
 *
 */
CTracePipeReceiver::CTracePipeReceiver(const char* szName)
{
    m_Name = szName;
    
    m_PipeName = m_Name + "_Pipe";
}


/**
 *
 */
CTracePipeReceiver::~CTracePipeReceiver()
{
}



/**
 *
 */
void CTracePipeReceiver::Start()
{
    Nyx::CAString       HostName;
    Nyx::CAString       HostIp;
    Nyx::NyxResult      res;
    
    m_refNxConnection = NyxNet::CNxConnection::Alloc();
    m_refNxConnection->SetConnectionHandler(static_cast<NyxNet::INxConnectionHandler*>(this));
    
    m_refPipeServer = NyxNet::CPipeServer::Alloc();
    m_refPipeServer->Create( m_PipeName.c_str(), 4096, m_refNxConnection );
    m_refPipeServer->Start();
    
    m_refOutConnection = NyxNet::CNxConnection::Alloc();
    
    m_refOutSocket = NyxNet::CTcpIpSocket::Alloc();
    res = NyxNet::CModule::Default()->GetHostname( HostName );
    res = NyxNet::CModule::Default()->GetHostIp( HostName.c_str(), HostIp );
    
    m_refOutConnection->Open( m_refOutSocket );
    m_refOutSocket->Create( HostIp.c_str(), 8500 );
    m_refOutSocket->Connect();
}


/**
 *
 */
void CTracePipeReceiver::Stop()
{
    m_refPipeServer->Stop();
    m_refOutSocket->Disconnect();
    m_refOutConnection->Close();
}


/**
 *
 */
void CTracePipeReceiver::HandleStream( NyxNet::INxStreamRW& rStream )
{
    NyxNet::CNxStreamReader     Reader(rStream);
    NyxNet::NxDataSize          TotalSize = 0;
    Nyx::UInt32                 SectionsCount = 0;
    Nyx::UInt32                 OutSectionsCount = 0;
    
    if ( !m_refOutSocket->Valid() )
        m_refOutSocket->Connect();
    
    NyxNet::CNxStreamWriter     OutWriter( (NyxNet::CNxConnection*)m_refOutConnection, NyxNet::eNxDT_TraceData );
    
    try
    {
        // read sections count
        {
            NyxNet::CNxSectionStreamReader        SectionReader(Reader);
            
            m_Buffer.Resize(SectionReader.Size());
            SectionReader.Read(m_Buffer, SectionReader.Size());
            
            SectionsCount = *m_Buffer.GetBufferAs<Nyx::UInt32>();
            
            OutSectionsCount = SectionsCount + 1;

            NyxNet::CNxSectionStreamWriter          SectionWriter(OutWriter, sizeof(OutSectionsCount));
            SectionWriter.Write(&SectionsCount, sizeof(OutSectionsCount));
        }
        
        //
        // write name
        //
        
        {
            NyxNet::NxDataSize                  size = (NyxNet::NxDataSize)m_Name.length() + 1;
            NyxNet::CNxSectionStreamWriter      SectionWriter(OutWriter, size);
            
            SectionWriter.Write( m_Name.BufferPtr(), size );
            
        }
        
        while ( SectionsCount -- > 0 )
        {
            NyxNet::CNxSectionStreamReader        SectionReader(Reader);
            
            m_Buffer.Resize(SectionReader.Size());
            SectionReader.Read(m_Buffer, SectionReader.Size());
            TotalSize += SectionReader.Size();
            
            NyxNet::CNxSectionStreamWriter          SectionWriter(OutWriter, SectionReader.Size());
            SectionWriter.Write( m_Buffer.GetBufferAs<void*>(), SectionReader.Size());
        }
    }
    catch (...)
    {
        Nyx::CTraceStream(0x0).Write("Error reading from pipe");
    }
    
//    Nyx::CTraceStream(0x0).Write(L"Read %i data from pipe %S", TotalSize, m_PipeName.c_str());
    Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"Read ") << Nyx::CTF_Int(TotalSize) << Nyx::CTF_Text(L" bytes from pipe : ") << Nyx::CTF_AnsiText(m_PipeName.c_str());
}


/**
 *
 */
Nyx::NyxResult CTracePipeReceiver::OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler )
{
    pCloneHandler = static_cast<INxConnectionHandler*>(this);
    return Nyx::kNyxRes_Success;
}


/**
 *
 */
void CTracePipeReceiver::OnConnectionTerminated( NyxNet::IConnection* pConnection )
{
    
}


/**
 *
 */
NyxNet::NxDataSize CTracePipeReceiver::ReadSection( NyxNet::CNxStreamReader& Reader )
{
    NyxNet::CNxSectionStreamReader        SectionReader(Reader);
    
    m_Buffer.Resize(SectionReader.Size());
    SectionReader.Read(m_Buffer, SectionReader.Size());
    
    return SectionReader.Size();
}
