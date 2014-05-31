#include "ConfigWriter.hpp"
#include "ServerAccess/TraceServerPortal.h"
#include "TraceClientApp.h"


CConfigWriter::CConfigWriter() : QObject()
{
}


CConfigWriter::~CConfigWriter()
{
}


void CConfigWriter::Save()
{
    CTraceClientApp&    rApp = CTraceClientApp::Instance();
    CTraceServerPortal& rPortal = rApp.TraceServerPortal();

    QSettings       settings(QSettings::IniFormat, QSettings::UserScope, "Nyx", "NyxTraceViewer");

    settings.beginGroup("TraceServer");

    settings.setValue("URI", QVariant(rPortal.server()));
    settings.setValue("traceClientName", QVariant(rPortal.traceClientName()));

    settings.endGroup();
}

