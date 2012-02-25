#include <QtGui/QApplication>
//#include "mainwindow.h"

#include <Nyx.hpp>
#include <NyxNet.hpp>
#include <NyxConsoleTraceOutput.hpp>

#include "TraceClientCoreModule.hpp"
#include "PipeTraceFeeder.hpp"
#include "TraceClientApp.hpp"

#include "StatusUpdaters/UISensorsFactory.hpp"

#include <NyxLocalTime.hpp>

Nyx::CTraceStream& operator << ( Nyx::CTraceStream& stream, const wchar_t* wszText )
{
    stream << Nyx::CTF_Text(wszText);
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

    TraceClientCore::CModule                    TraceClientCoreModule;

    Nyx::CLocalTime ltime = Nyx::CLocalTime::Get();

    Nyx::CTraceStream(0x0) << L"hello";

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
