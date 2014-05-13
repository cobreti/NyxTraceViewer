#include "SettingsPanel.h"
#include "ui_SettingsPanel.h"
#include "MainWindow/TcpIpSettingsPanel.h"
#include "TraceClientApp.h"
#include "ServerAccess/TraceServerPortal.h"
#include "ServerAccess/TraceServerMonitor.h"


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


void CSettingsPanel::onTraceDirectoryPortChanged(const QString &text)
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
    QString port = ui->TraceDirectoryPort->text();
    QString fullAddress = QString("%1:%2").arg(server).arg(port);

    CTraceClientApp& rApp = CTraceClientApp::Instance();
    CTraceServerPortal& rServerPortal = rApp.TraceServerPortal();

    rServerPortal.setServer(fullAddress);
    rServerPortal.setTraceClient(name);

    ui->applyButton->setEnabled(false);
    ui->name->setEnabled(false);
    ui->TraceDirectoryServer->setEnabled(false);
    ui->TraceDirectoryPort->setEnabled(false);

    rApp.TraceServerMonitor().Start();
}


void CSettingsPanel::onClientRegistered(int id)
{
    CTraceClientApp&    rApp = CTraceClientApp::Instance();

    rApp.AppSettings().clientId() = id;
    rApp.TraceServerPortal().getDevices();

    ui->statusLabel->setText("<font color='green'>connected to server</font>");
}


void CSettingsPanel::onClientRegisterFailed()
{
    ui->statusLabel->setText("<font color='red'>failure to connect to server</font>");
    ui->applyButton->setEnabled(true);
    ui->name->setEnabled(true);
    ui->TraceDirectoryServer->setEnabled(true);
    ui->TraceDirectoryPort->setEnabled(true);
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

    connect( ui->TraceDirectoryServer, SIGNAL(textChanged(QString)),
             this, SLOT(onTraceDirectoryServerChanged(QString)));
    connect( ui->TraceDirectoryPort, SIGNAL(textChanged(QString)),
             this, SLOT(onTraceDirectoryPortChanged(QString)));
    connect( ui->name, SIGNAL(textChanged(QString)),
             this, SLOT(onNameChanged(QString)));
    connect( ui->applyButton, SIGNAL(clicked()),
             this, SLOT(onApply()));
}



void CSettingsPanel::ValidateInputs()
{
    QString name = ui->name->text();
    QString address = ui->TraceDirectoryServer->text();
    QString port = ui->TraceDirectoryPort->text();

    ui->applyButton->setEnabled( !name.isEmpty() && !address.isEmpty() && !port.isEmpty() );
}


void CSettingsPanel::showEvent(QShowEvent *)
{
    CTraceServerPortal&     rPortal = CTraceClientApp::Instance().TraceServerPortal();
    CTraceServerMonitor&    rMonitor = CTraceClientApp::Instance().TraceServerMonitor();

    if ( rMonitor.active() )
    {
        ui->applyButton->setEnabled(false);
        ui->name->setEnabled(false);
        ui->TraceDirectoryServer->setEnabled(false);
        ui->TraceDirectoryPort->setEnabled(false);
    }
    else
    {
        ValidateInputs();
    }

    connect(    &rPortal, SIGNAL(clientRegistered(int)),
                this, SLOT(onClientRegistered(int)) );
    connect(    &rPortal, SIGNAL(clientRegisterFailed()),
                this, SLOT(onClientRegisterFailed()));
}


void CSettingsPanel::hideEvent(QHideEvent *)
{
    CTraceServerPortal&     rPortal = CTraceClientApp::Instance().TraceServerPortal();

    disconnect( &rPortal, SIGNAL(clientRegistered(int)),
                this, SLOT(onClientRegistered(int)) );
    disconnect( &rPortal, SIGNAL(clientRegisterFailed()),
                this, SLOT(onClientRegisterFailed()) );

    ui->statusLabel->clear();
}

