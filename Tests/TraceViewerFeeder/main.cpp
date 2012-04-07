#include "TraceViewerFeeder.h"
#include <QtGui/QApplication>

#include <Nyx.hpp>
#include <NyxNet.hpp>

#include <NyxConsoleTraceOutput.hpp>

int main(int argc, char *argv[])
{
    Nyx::CModuleRef             refModule = Nyx::CModule::Alloc();
    NyxNet::CModuleRef          refNetModule = NyxNet::CModule::Alloc();

    Nyx::CTraceCompositorRef    refTraceCompositor = Nyx::CTraceCompositor::Alloc();

    refTraceCompositor->SetOutput(Nyx::CConsoleTraceOutput::Alloc());

    QApplication a(argc, argv);
    CTraceViewerFeeder w;
    w.show();
    int ret = a.exec();

    return ret;
}
