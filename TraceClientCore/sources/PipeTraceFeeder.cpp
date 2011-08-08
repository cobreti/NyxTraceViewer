#include "PipeTraceFeeder.hpp"
#include "TraceInserter.hpp"
#include "TraceData.hpp"
#include "TracesPool.hpp"


/**
 *
 */
TraceClientCore::CPipeTraceFeeder::CPipeTraceFeeder( TraceClientCore::CTracesPool* pOwnerPool ) :
CTraceFeeder(pOwnerPool),
m_TracesCount(0),
m_pLastTrace(NULL)
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
    m_Name = GetOwnerPool()->Name().c_str();
	m_Name += "_Pipe";
    m_pLastTrace = NULL;

	m_refNxConnection  = NyxNet::CNxConnection::Alloc();
	m_refNxConnection->SetConnectionHandler( static_cast<NyxNet::INxConnectionHandler*>(this) );
	m_refServer = NyxNet::CPipeServer::Alloc();
	
    //m_refServer->Create( "Default_Pipe", 4096, m_refNxConnection );
    m_refServer->Create( m_Name.c_str(), 4096, m_refNxConnection );
	
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
	Nyx::UInt32						version = 0;
    Nyx::NyxResult                  res;
	
    try
    {
	    if ( Reader.Valid() )
	    {
		    pTraceData = new (GetOwnerPool()->MemoryPool())CTraceData(GetOwnerPool()->MemoryPool());
    	
		    // version
		    {
			    NyxNet::CNxSectionStreamReader		SectionReader(Reader);

			    m_ReadBuffer.Resize(SectionReader.Size());
			    res = SectionReader.Read(m_ReadBuffer, SectionReader.Size());
                if ( Nyx::Failed(res) )
                    throw Nyx::CException("failure to read version");

			    version = *m_ReadBuffer.GetBufferAs<Nyx::UInt32>();
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
    			
			    switch ( version )
			    {
				    case 0x0001:
					    pTraceData->Data() = m_ReadBuffer.GetBufferAs<char>();
					    break;
				    case 0x0002:
					    pTraceData->Data() = m_ReadBuffer.GetBufferAs<wchar_t>();
					    break;
			    };
		    }

            if ( m_TracesCount == 0 )
            {
                CTraceData*   pConnTraceData = new (GetOwnerPool()->MemoryPool())TraceClientCore::CTraceData(GetOwnerPool()->MemoryPool());

                pConnTraceData->Type() = CTraceData::eTT_ConnectionStatus_Connection;
                pConnTraceData->Data() = L"Connection";
                pConnTraceData->TickCount() = pTraceData->TickCount();
                pConnTraceData->OwnerPool() = GetOwnerPool();
                GetOwnerPool()->Repository().Insert(pConnTraceData);
            }

    		
            pTraceData->OwnerPool() = GetOwnerPool();
            GetOwnerPool()->Repository().Insert(pTraceData);
            
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
        CTraceData*       pTraceData = new (GetOwnerPool()->MemoryPool())TraceClientCore::CTraceData(GetOwnerPool()->MemoryPool());

        pTraceData->Type() = CTraceData::eTT_ConnectionStatus_Disconnection;
        pTraceData->Data() = L"Disconnection";
        pTraceData->TickCount() = m_pLastTrace->TickCount();
        pTraceData->OwnerPool() =  GetOwnerPool();
        GetOwnerPool()->Repository().Insert(pTraceData);
    }

    m_TracesCount = 0;
}


