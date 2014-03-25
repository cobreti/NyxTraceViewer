#include "SettingsPanel.h"
#include "ui_SettingsPanel.h"
#include "MainWindow/TcpIpSettingsPanel.h"


CSettingsPanel::CSettingsPanel() : QWidget(),
    ui(new Ui::SettingsPanel()),
    m_pTxtTcpIpSettingsPanel(NULL)
{
    ui->setupUi(this);

    Init();
}


CSettingsPanel::~CSettingsPanel()
{

}


void CSettingsPanel::onTraceDirectoryServerChanged(const QString& text)
{
    ui->applyButton->setEnabled(true);
}


void CSettingsPanel::Init()
{
    m_pTxtTcpIpSettingsPanel = new CTcpIpSettingsPanel();
    m_pTxtTcpIpSettingsPanel->SetTracesReceiversSvr( &TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr(1) );
    ui->TxtTracePortLayout->addWidget(m_pTxtTcpIpSettingsPanel);

    connect( ui->TraceDirectoryServer, SIGNAL(textChanged(QString)), this, SLOT(onTraceDirectoryServerChanged(QString)));
}


void CSettingsPanel::showEvent(QShowEvent *)
{
    ui->applyButton->setEnabled(false);
}


void CSettingsPanel::hideEvent(QHideEvent *)
{

}

