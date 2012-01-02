#include "TracePipeReceiver.hpp"


/**
 *
 */
CTracePipeReceiver::CTracePipeReceiver(const char* szPipeName)
{
    m_PipeName = szPipeName;
    m_PipeName += "_Pipe";
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
    m_refNxConnection = NyxNet::CNxConnection::Alloc();
    m_refNxConnection->SetConnectionHandler(static_cast<NyxNet::INxConnectionHandler*>(this));
    
    m_refPipeServer = NyxNet::CPipeServer::Alloc();
    m_refPipeServer->Create( m_PipeName.c_str(), 4096, m_refNxConnection );
    m_refPipeServer->Start();
}


/**
 *
 */
void CTracePipeReceiver::Stop()
{
    m_refPipeServer->Stop();
}


/**
 *
 */
void CTracePipeReceiver::HandleStream( NyxNet::INxStreamRW& rStream )
{
    NyxNet::CNxStreamReader     Reader(rStream);
    NyxNet::NxDataSize          TotalSize = 0;
    
    try
    {
        TotalSize += ReadSection(Reader); // flags
        TotalSize += ReadSection(Reader); // thread id
        TotalSize += ReadSection(Reader); // tickcount
        TotalSize += ReadSection(Reader); // data
    }
    catch (...)
    {
        Nyx::CTraceStream(0x0).Write("Error reading from pipe");
    }
    
    Nyx::CTraceStream(0x0).Write(L"Read %i data from pipe %s", TotalSize, m_PipeName.c_str());
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

