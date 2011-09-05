#include <NyxNet.hpp>
#include <NyxNetPipeTraceOutput.hpp>
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
    m_refTraceCompositor->SetOutput( NyxNet::CPipeTraceOutput::Alloc(name.c_str()) );
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


