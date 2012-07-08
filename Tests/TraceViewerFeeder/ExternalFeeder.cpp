#include "ExternalFeeder.hpp"
#include "FeederSettings.hpp"

#include "NyxTraceViewerConnection.hpp"
#include "FeederSettings.hpp"
#include "FeederSource.hpp"

/**
 *
 */
CExternalFeeder::CExternalFeeder() :
CFeederBase()
{
}


/**
 *
 */
CExternalFeeder::~CExternalFeeder()
{
}


/**
 *
 */
void CExternalFeeder::OnBegin()
{
    Nyx::CAString     name;
    name = Settings().Name().c_str();
    Nyx::CTraceViewerConnection_Pipe_Ansi::CreateInstance(name.c_str());
//    CTraceClientLink::CreateInstance(name.c_str(), CTraceClientLink::eCT_Ansi);
}


/**
 *
 */
void CExternalFeeder::OnEnd()
{
    Nyx::CTraceViewerConnection::ReleaseInstance();
}


/**
 *
 */
void CExternalFeeder::OnSendTrace()
{
    static      int i = 0;

    if ( Settings().FeederSource() )
    {
        Nyx::CWString   text;
        Nyx::CAString   Atext;

        Settings().FeederSource()->GetLine(text);

        Atext = text;

        Nyx::CTraceViewerConnection::Instance().Write(Atext.c_str());
//        CTraceClientLink::Instance().Write(Atext.c_str());
        //CTraceClientLink::Instance().Write(L"Test with parameters : str = '%s' and value = %i (%Xh)", L"string value", i, i);
    }
}

