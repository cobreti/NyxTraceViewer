#include "TcpIpSettingsPanel.h"

#include "ui_TcpIpSettingsPanel.h"


/**
 *
 */
class CReceiversListenerBridge : public Nyx::CObject_Impl<TraceClientCore::ITcpTracesReceiversListener>
{
public:
    CReceiversListenerBridge( CTcpIpSettingsPanel& rPanel ) :
        m_rPanel(rPanel)
    {
    }

    ~CReceiversListenerBridge()
    {
    }

    virtual void OnReceiversStarted()
    {
//        m_rPanel.UpdateStartStopButtons();
        emit m_rPanel.TcpReceiversStateChanged();
    }

    virtual void OnReceiversStopped()
    {
//        m_rPanel.UpdateStartStopButtons();
        emit m_rPanel.TcpReceiversStateChanged();
    }

protected:

    CTcpIpSettingsPanel&        m_rPanel;
};


/**
 *
 */
CTcpIpSettingsPanel::CTcpIpSettingsPanel(QWidget *parent) :
    QWidget(parent),
    ui( new Ui::TcpIpSettingsPanel() )
{
    ui->setupUi(this);

    {
        TraceClientCore::CTcpTracesReceivers&   rReceivers = TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceivers();

        rReceivers.Listeners()->Add( new CReceiversListenerBridge(*this) );
        m_Settings = rReceivers.Settings();
    }

    connect( ui->m_btnStartStop, SIGNAL(clicked()), this, SLOT(OnStartStop()) );
    connect( this, SIGNAL(TcpReceiversStateChanged()), this, SLOT(OnTcpReceiversStateChanged()) );
}


/**
 *
 */
void CTcpIpSettingsPanel::OnStartStop()
{
    TraceClientCore::CTcpTracesReceivers&   rTracesReceivers = TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceivers();

    ui->m_btnStartStop->setEnabled(false);

    if ( rTracesReceivers.IsRunning() )
        rTracesReceivers.Stop();
    else
    {
        m_Settings.PortNumber() = ui->m_editTcpIpPortNumber->text().toInt();
        rTracesReceivers.Start(m_Settings);
    }
}


/**
 *
 */
void CTcpIpSettingsPanel::OnTcpReceiversStateChanged()
{
    UpdateStartStopButtons();
}


/**
 *
 */
void CTcpIpSettingsPanel::showEvent(QShowEvent *)
{
    UpdateStartStopButtons();
}


/**
 *
 */
void CTcpIpSettingsPanel::UpdateStartStopButtons()
{
    QIcon               StopIcon(":/TcpIpSettingsPanel/Stop");
    QIcon               StartIcon(":/TcpIpSettingsPanel/Start");

    QString             portNumber;

    portNumber.setNum( m_Settings.PortNumber() );

    ui->m_editTcpIpPortNumber->setText(portNumber);

    if ( TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceivers().IsRunning() )
    {
        ui->m_btnStartStop->setIcon(StopIcon);
        ui->m_editTcpIpPortNumber->setEnabled(false);
        m_Settings = TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceivers().Settings();
    }
    else
    {
        ui->m_btnStartStop->setIcon(StartIcon);
        ui->m_editTcpIpPortNumber->setEnabled(true);
    }

    ui->m_btnStartStop->setEnabled(true);
}

