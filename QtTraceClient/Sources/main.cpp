//#include "mainwindow.h"

#include <Nyx.hpp>
#include <NyxNet.hpp>
#include <NyxConsoleTraceOutput.hpp>

#include "TraceClientCoreModule.hpp"
#include "PipeTraceFeeder.hpp"
#include "TraceClientApp.h"

#include "StatusUpdaters/UISensorsFactory.hpp"

#include <NyxLocalTime.hpp>

#include <QtGui/QApplication>

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/crypto.h>

#define NYXTRACE(filter, output)    { Nyx::CTraceStream stream(filter); stream << output; }



Nyx::CTraceStream& operator << ( Nyx::CTraceStream& stream, const Nyx::CLocalTime& ltime )
{
    stream << ltime.Hours() << L":" << ltime.Minutes() << L":" << ltime.Seconds();
    return stream;
}




int main(int argc, char *argv[])
{
    Nyx::CModuleRef                             refModule = Nyx::CModule::Alloc();
    NyxNet::CModuleRef                          refNetModule = NyxNet::CModule::Alloc();

#if defined(_DEBUG)
	Nyx::CTraceCompositorRef                    refTraceCompositor = Nyx::CTraceCompositor::Alloc();

    refTraceCompositor->SetOutput(Nyx::CConsoleTraceOutput::Alloc());
//    refTraceCompositor->SetOutput( NyxNet::CPipeTraceOutput::Alloc("TraceViewer"));
#endif

    CRYPTO_malloc_init(); // Initialize malloc, free, etc for OpenSSL's use
    SSL_library_init(); // Initialize OpenSSL's SSL libraries
    SSL_load_error_strings(); // Load SSL error strings
    ERR_load_BIO_strings(); // Load BIO error strings
    OpenSSL_add_all_algorithms(); // Load all available encryption algorithms

    Nyx::CLocalTime     ltime = Nyx::CLocalTime::Get();

    NYXTRACE(0x0, L"current time is : " << ltime << L":");

//    Nyx::CTraceStream(0x0) << ltime.Hours() << L":"
//                           << ltime.Minutes() << L":"
//                           << ltime.Seconds();

    TraceClientCore::CModule                    TraceClientCoreModule;

    Nyx::CTraceStream(0x0).Write(L"Application starting");

    CTraceClientApp     TheApp;

    TheApp.Init(argc, argv);
    TheApp.Run();
    TheApp.Destroy();

	CUISensorsFactory::Terminate();

	TraceClientCoreModule.TracesPools().Clear();

    Nyx::CTraceStream(0x0).Write(L"Application ending");

    return TheApp.ReturnValue();
}

