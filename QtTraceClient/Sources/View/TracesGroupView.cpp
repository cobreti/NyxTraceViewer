#include "TracesGroupView.h"
#include "TraceClientApp.h"

CTracesGroupView::CTracesGroupView() :
    m_bKeepAtEnd(false)
{
    m_ColumnsSettings = CTraceClientApp::Instance().AppSettings().DefaultViewSettings().ColumnsSettings();
}


CTracesGroupView::~CTracesGroupView()
{
}


