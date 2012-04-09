#include "TraceLink.hpp"
#include <stdarg.h>


/**
 *
 */
CTraceLink::CTraceLink() :
m_NextAvailID(0x0001),
m_AnsiBuffer(kBufferSize),
m_WCharBuffer(kBufferSize)
{
	m_refModule = Nyx::CModule::Alloc();
    m_refMutex = Nyx::CMutex::Alloc();
	m_refTraceCompositor = Nyx::CTraceCompositor::Alloc(Nyx::eTCCS_Ansi, false);
	m_refTraceCompositor->SetOutput( NyxNet::CPipeTraceOutput::Alloc("TraceClientLink") );
}


/**
 *
 */
CTraceLink::~CTraceLink()
{
    m_refMutex = NULL;
    m_refModule = NULL;
    m_refTraceCompositor = NULL;
}


/**
 *
 */
unsigned int CTraceLink::CreateTraceLink( const char* szName, int nType )
{
    Nyx::ETraceCompositorCharSet    eCharSet = Nyx::eTCCS_Ansi;
	Nyx::CTraceCompositorRef		refTraceCompositor;
	unsigned int					id = m_NextAvailID ++;

    if ( nType != 0 )
        eCharSet = Nyx::eTCCS_WideChar;

    refTraceCompositor = Nyx::CTraceCompositor::Alloc(eCharSet, false);

	m_TraceCompositorsTable.insert( std::make_pair(id, refTraceCompositor) );
	
	refTraceCompositor->SetOutput( NyxNet::CPipeTraceOutput::Alloc(szName) );

	return id;
}


/**
 *
 */
void CTraceLink::ReleaseTraceLink( const unsigned int& id )
{
	TraceCompositorsMap::iterator		pos = m_TraceCompositorsTable.find(id);

	m_TraceCompositorsTable.erase(pos);
}


/**
 *
 */
void CTraceLink::WriteTraceA( const unsigned int& id, const char* szData, va_list args )
{
    Nyx::TLock<Nyx::CMutex>     Lock(m_refMutex, true);

	TraceCompositorsMap::iterator		pos = m_TraceCompositorsTable.find(id);

	if ( pos != m_TraceCompositorsTable.end() )
	{
		Nyx::CTraceCompositorRef	refTraceCompositor = pos->second;
		Nyx::CTraceStream			stream(0xFF, refTraceCompositor);

//        vsprintf(m_AnsiBuffer, szData, args);
		m_AnsiBuffer.Format(szData, args);

		stream.Write(m_AnsiBuffer.c_str());
	}
}


/**
 *
 */
void CTraceLink::WriteTraceW( const unsigned int& id, const wchar_t* wszData, va_list args )
{
    Nyx::TLock<Nyx::CMutex>     Lock(m_refMutex, true);

	TraceCompositorsMap::iterator		pos = m_TraceCompositorsTable.find(id);

	if ( pos != m_TraceCompositorsTable.end() )
	{
		Nyx::CTraceCompositorRef	refTraceCompositor = pos->second;
		Nyx::CTraceStream			stream(0xFF, refTraceCompositor);

//        vswprintf(m_WCharBuffer, kBufferSize, wszData, args);
		m_WCharBuffer.Format(wszData, args);

		stream.Write(m_WCharBuffer.c_str());
	}
}