#include <NyxNet.hpp>
#include <NyxNetPipeTraceOutput.hpp>
#include <NyxNetTcpIpTraceOutput.hpp>
#include <NyxAnsiFile.hpp>

#include "NyxFeeder.hpp"
#include "FeederSettings.hpp"
#include "FeederSource.hpp"

/**
 *
 */
CNyxFeeder::CNyxFeeder() : 
CFeederBase(),
m_Index(0)
{
}


/**
 *
 */
CNyxFeeder::~CNyxFeeder()
{
}


/**
 *
 */
void CNyxFeeder::OnBegin()
{
    Nyx::CAString     name;
	name = Settings().Name();

	m_refTraceCompositor = Nyx::CTraceCompositor::Alloc(Nyx::eTCCS_WideChar, false);

    switch ( Settings().ApiType() )
    {
        case CFeederSettings::eTAPI_NyxPipe:
            m_refTraceCompositor->SetOutput( NyxNet::CPipeTraceOutput::Alloc(name.c_str()) );
            break;

        case CFeederSettings::eTAPI_NyxTcpIp:
            m_refTraceCompositor->SetOutput(    NyxNet::CTcpIpTraceOutput::Alloc(name.c_str(),
                                                Settings().TcpIpAddress().c_str(),
                                                Settings().PortNumber() ) );
            break;
    };
}


/**
 *
 */
void CNyxFeeder::OnEnd()
{
    m_refTraceCompositor = NULL;
}


/**
 *
 */
void CNyxFeeder::OnSendTrace()
{
    if ( Settings().FeederSource() )
    {
        Nyx::CWString   text;

        Settings().FeederSource()->GetLine(text);

        Nyx::CTraceStream(0x0, m_refTraceCompositor) << Nyx::CTF_Text( text.c_str() );
    }
}


