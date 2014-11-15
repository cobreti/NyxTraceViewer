#include "PipeTraceFeeder.hpp"
#include "TraceInserter.hpp"
#include "TraceData.hpp"
#include "TracesPool.hpp"
#include "NyxNetTraceFlags.hpp"
#include "TraceChannel.hpp"


/**
 *
 */
TraceClientCore::CPipeTraceFeeder::CPipeTraceFeeder( TraceClientCore::CTraceChannel* pChannel ) :
CTraceFeeder(pChannel),
m_TracesCount(0),
m_pLastTrace(NULL),
m_TraceReader(pChannel->Pool())
{
}


/**
 *
 */
TraceClientCore::CPipeTraceFeeder::~CPipeTraceFeeder()
{
	Stop();
}


/**
 *
 */
void TraceClientCore::CPipeTraceFeeder::Start()
{
    m_Name = Channel()->Name().toStdString().c_str();
	m_Name += "_Pipe";
    m_pLastTrace = NULL;

	m_refNxConnection  = NyxNet::CNxConnection::Alloc();
	m_refNxConnection->SetConnectionHandler( static_cast<NyxNet::INxConnectionHandler*>(this) );
	m_refServer = NyxNet::CPipeServer::Alloc();
	
    m_refServer->Create( m_Name.c_str(), 1024 * 1024, m_refNxConnection );
	
	m_refServer->Start();
}


/**
 *
 */
void TraceClientCore::CPipeTraceFeeder::Stop()
{
	if ( m_refServer.Valid() )
		m_refServer->Stop();
		
	m_refServer = NULL;
	m_refNxConnection = NULL;
    m_pLastTrace = NULL;
}


/**
 *
 */
bool TraceClientCore::CPipeTraceFeeder::IsRunning() const
{
	return (m_refServer.Valid() && m_refServer->IsRunning());
}


/**
 *
 */
void TraceClientCore::CPipeTraceFeeder::HandleStream( NyxNet::INxStreamRW& rStream )
{
    NyxNet::CNxStreamReader			Reader(rStream);
	CTraceData*						pTraceData = NULL;
    Nyx::UInt32                     SectionsCount = 0;
    Nyx::NyxResult                  res;
	
    try
    {        
        // sections count
        {
            NyxNet::CNxSectionStreamReader      SectionReader(Reader);
            
            m_ReadBuffer.Resize(SectionReader.Size());
            res = SectionReader.Read(m_ReadBuffer, SectionReader.Size());
            if ( Nyx::Failed(res) )
                throw Nyx::CException("failure to read sections count");
            
            SectionsCount = *m_ReadBuffer.GetBufferAs<Nyx::UInt32>();
        }

        pTraceData = m_TraceReader.Read(SectionsCount, Reader);
        if ( pTraceData )
        {
            CTracesPool*        pPool = Channel()->Pool();

            if ( m_TracesCount == 0 )
            {
                CTraceData*         pConnTraceData = new CTraceData();

                pConnTraceData->Type() = CTraceData::eTT_ConnectionStatus_Connection;
                pConnTraceData->Data() = "Connection";
                pConnTraceData->TickCount() = pTraceData->TickCount();
                pConnTraceData->Flags() = pTraceData->Flags();
                pPool->Repository().Insert(pConnTraceData);
            }
        
            pPool->Repository().Insert(pTraceData);
            
            m_pLastTrace = pTraceData;

            ++ m_TracesCount;
	    }
    }
    catch (Nyx::CException& ex)
    {
        Nyx::CTraceStream(0x0).Write(L"HandleStream exception : %s", ex.Msg());
    }
}


/**
 *
 */
Nyx::NyxResult TraceClientCore::CPipeTraceFeeder::OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler )
{
	pCloneHandler = static_cast<NyxNet::INxConnectionHandler*>(this);
    
    return Nyx::kNyxRes_Success;
}


/**
 *
 */
void TraceClientCore::CPipeTraceFeeder::OnConnectionTerminated( NyxNet::IConnection* pConnection )
{
    if ( m_TracesCount > 0 )
    {
        CTracesPool*        pPool = Channel()->Pool();
        CTraceData*         pTraceData = new CTraceData();

        pTraceData->Type() = CTraceData::eTT_ConnectionStatus_Disconnection;
        pTraceData->Data() = "Disconnection";
        pTraceData->TickCount() = m_pLastTrace->TickCount();
        pPool->Repository().Insert(pTraceData);
    }

    m_TracesCount = 0;
}


