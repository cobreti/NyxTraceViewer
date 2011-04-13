#include "ExternalFeeder.hpp"
#include "FeederSettings.hpp"

#include "TraceClientLink.hpp"

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
    CTraceClientLink::CreateInstance(name.c_str(), CTraceClientLink::eCT_Ansi);
}


/**
 *
 */
void CExternalFeeder::OnEnd()
{
    CTraceClientLink::ReleaseInstance();
}


/**
 *
 */
void CExternalFeeder::OnSendTrace()
{
    static      int i = 0;
    Nyx::CAString     text;
    text = Settings().Text().c_str();

    CTraceClientLink::Instance().Write(text.c_str());
    //CTraceClientLink::Instance().Write(L"Test with parameters : str = '%s' and value = %i (%Xh)", L"string value", i, i);

    ++i;
    i << 2;
}

