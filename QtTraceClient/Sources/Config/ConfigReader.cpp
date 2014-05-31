#include <Nyx.hpp>

#include "ConfigReader.hpp"
#include "ServerAccess/TraceServerPortal.h"
#include "TraceClientApp.h"

#include <QSettings>

CConfigReader::CConfigReader() : QObject()
{
}


CConfigReader::~CConfigReader()
{
}


void CConfigReader::Load()
{
    CTraceClientApp&    rApp = CTraceClientApp::Instance();
    CTraceServerPortal& rPortal = rApp.TraceServerPortal();

    QSettings       settings(QSettings::IniFormat, QSettings::UserScope, "Nyx", "NyxTraceViewer");

    settings.beginGroup("TraceServer");

    if ( settings.contains("URI") )
    {
        QVariant serverURI = settings.value("URI");
        rPortal.server() = serverURI.toString();
    }

    if ( settings.contains("traceClientName") )
    {
        QVariant name = settings.value("traceClientName");
        rPortal.traceClientName() = name.toString();
    }

    settings.endGroup();
}

