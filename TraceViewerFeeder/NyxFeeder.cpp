#include <NyxNet.hpp>
#include <NyxNetPipeTraceOutput.hpp>

#include "NyxFeeder.hpp"
#include "FeederSettings.hpp"


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
    Nyx::CTraceStream(0x0, m_refTraceCompositor) << Nyx::CTF_Text( Settings().Text().c_str() )
            << Nyx::CTF_Text(L" [")
            << Nyx::CTF_Int(++m_Index)
            << Nyx::CTF_Text(L"]");
}

