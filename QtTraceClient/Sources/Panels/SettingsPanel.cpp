#include "SettingsPanel.h"
#include "ui_SettingsPanel.h"
#include "MainWindow/TcpIpSettingsPanel.h"
#include "TraceClientApp.h"
#include "ServerAccess/TraceServerPortal.h"


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
    ValidateInputs();
}


void CSettingsPanel::onNameChanged(const QString &text)
{
    ValidateInputs();
}


void CSettingsPanel::onApply()
{
    QString name = ui->name->text();
    QString server = ui->TraceDirectoryServer->text();

    CTraceServerPortal& rServerPortal = CTraceClientApp::Instance().TraceServerPortal();

    rServerPortal.setServer(server);
    rServerPortal.setTraceClient(name);
}


void CSettingsPanel::onClientRegistered(int id)
{
    CTraceClientApp::Instance().AppSettings().clientId() = id;
}


void CSettingsPanel::Init()
{
    m_pTxtTcpIpSettingsPanel = new CTcpIpSettingsPanel();
    m_pTxtTcpIpSettingsPanel->SetTracesReceiversSvr( &TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr(1) );
    ui->TxtTracePortLayout->addWidget(m_pTxtTcpIpSettingsPanel);
    ui->TxtTracePortLayout->update();
    ui->frame->layout()->update();
    QRect rcLayout = ui->TxtTracePortLayout->contentsRect();
    QRect rcCtrl = m_pTxtTcpIpSettingsPanel->rect();

    connect( ui->TraceDirectoryServer, SIGNAL(textChanged(QString)), this, SLOT(onTraceDirectoryServerChanged(QString)));
    connect( ui->name, SIGNAL(textChanged(QString)), this, SLOT(onNameChanged(QString)));
    connect( ui->applyButton, SIGNAL(clicked()), this, SLOT(onApply()));
}



void CSettingsPanel::ValidateInputs()
{
    QString name = ui->name->text();

    ui->applyButton->setEnabled( !name.isEmpty() );
}


void CSettingsPanel::showEvent(QShowEvent *)
{
    CTraceServerPortal&     rPortal = CTraceClientApp::Instance().TraceServerPortal();

    ui->applyButton->setEnabled(false);

    QRect rcLayout = ui->TxtTracePortLayout->contentsRect();
    QRect rcCtrl = m_pTxtTcpIpSettingsPanel->rect();

    connect(    &rPortal, SIGNAL(clientRegistered(int)),
                this, SLOT(onClientRegistered(int)) );
}


void CSettingsPanel::hideEvent(QHideEvent *)
{
    CTraceServerPortal&     rPortal = CTraceClientApp::Instance().TraceServerPortal();

    disconnect( &rPortal, SIGNAL(clientRegistered(int)),
                this, SLOT(onClientRegistered(int)) );
}

