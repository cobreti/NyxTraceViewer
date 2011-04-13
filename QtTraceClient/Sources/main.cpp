#include <QtGui/QApplication>
#include "mainwindow.h"

#include <Nyx.hpp>
#include <NyxNet.hpp>
#include <NyxConsoleTraceOutput.hpp>

#include "TraceClientCoreModule.hpp"
#include "PipeTraceFeeder.hpp"

#include "StatusUpdaters/UISensorsFactory.hpp"


int main(int argc, char *argv[])
{
    Nyx::CModuleRef                             refModule = Nyx::CModule::Alloc();
    NyxNet::CModuleRef                          refNetModule = NyxNet::CModule::Alloc();

#if defined(_DEBUG)
	Nyx::CTraceCompositorRef                    refTraceCompositor = Nyx::CTraceCompositor::Alloc();

    refTraceCompositor->SetOutput(Nyx::CConsoleTraceOutput::Alloc());
#endif

    TraceClientCore::CModule                    TraceClientCoreModule;

    Nyx::CTraceStream(0x0).Write(L"Application starting");

    QApplication a(argc, argv);
    CMainWindow* pMainWindow = new CMainWindow();
	pMainWindow->show();
    int ret = a.exec();

	delete pMainWindow;
	pMainWindow = NULL;

	CUISensorsFactory::Terminate();

	//w.close();

	TraceClientCoreModule.TracesPools().Clear();

    Nyx::CTraceStream(0x0).Write(L"Application ending");

    return ret;
}
