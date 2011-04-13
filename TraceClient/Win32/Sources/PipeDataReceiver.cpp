#include "PipeDataReceiver.hpp"
#include "TraceData.hpp"
#include "PipeTraceFeeder.hpp"

/**
 *
 */
CPipeDataReceiver::CPipeDataReceiver( CPipeTraceFeeder& rFeeder ) :
m_rFeeder(rFeeder)
{
}


/**
 *
 */
CPipeDataReceiver::~CPipeDataReceiver()
{
}

/**
 *
 */
void CPipeDataReceiver::HandleStream( NyxNet::INxStreamRW& rStream )
{
	NyxNet::CNxStreamReader				Reader(rStream);
	CTraceDataRef						refTraceData = new CTraceData();

	if ( Reader.Valid() )
	{
		// thread id
		{
			NyxNet::CNxSectionStreamReader		SectionReader(Reader);

			m_ReadBuffer.Resize(SectionReader.Size());

			SectionReader.Read(m_ReadBuffer, SectionReader.Size());

			refTraceData->ThreadId() = Nyx::CString::Alloc();
			refTraceData->ThreadId()->Set(m_ReadBuffer.GetBufferAs<char>());
		}

		// tick count
		{
			NyxNet::CNxSectionStreamReader		SectionReader(Reader);

			m_ReadBuffer.Resize(SectionReader.Size());

			SectionReader.Read(m_ReadBuffer, SectionReader.Size());

			refTraceData->TickCount() = Nyx::CString::Alloc();
			refTraceData->TickCount()->Set(m_ReadBuffer.GetBufferAs<char>());
		}

		// data
		{
			NyxNet::CNxSectionStreamReader		SectionReader(Reader);

			m_ReadBuffer.Resize(SectionReader.Size());

			SectionReader.Read(m_ReadBuffer, SectionReader.Size());

			refTraceData->Data() = Nyx::CString::Alloc();
			refTraceData->Data()->Set(m_ReadBuffer.GetBufferAs<wchar_t>());
		}

		{
			CPipeTraceFeeder::Accessor		FeederAccess(m_rFeeder);

			if ( FeederAccess )
				FeederAccess->FeederLinks().Feed(refTraceData);
		}
	}
}


/**
 *
 */
Nyx::NyxResult CPipeDataReceiver::OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler )
{
	pCloneHandler = this;
	return Nyx::kNyxRes_Success;
}


/**
 *
 */
void CPipeDataReceiver::OnConnectionTerminated( NyxNet::IConnection* pConnection )
{
}

