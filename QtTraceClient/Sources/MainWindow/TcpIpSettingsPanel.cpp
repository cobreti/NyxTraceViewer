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
        TraceClientCore::CTcpTracesReceiversSvr&   rReceiversSvr = TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr();

        rReceiversSvr.Listeners()->Add( new CReceiversListenerBridge(*this) );
        m_Settings = rReceiversSvr.Settings();
    }

    connect( ui->m_btnStartStop, SIGNAL(clicked()),
             this, SLOT(OnStartStop()) );
    connect( this, SIGNAL(TcpReceiversStateChanged()),
             this, SLOT(OnTcpReceiversStateChanged()) );
    connect( ui->m_editTcpIpPortNumber, SIGNAL(textChanged(QString)),
             this, SLOT(OnPortNumberChanged(QString)));
}


/**
 *
 */
void CTcpIpSettingsPanel::OnStartStop()
{
    TraceClientCore::CTcpTracesReceiversSvr&   rTracesReceiversSvr = TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr();

    ui->m_btnStartStop->setEnabled(false);

    if ( rTracesReceiversSvr.IsRunning() )
        rTracesReceiversSvr.Stop();
    else
    {
        m_Settings.PortNumber() = ui->m_editTcpIpPortNumber->text().toInt();
        rTracesReceiversSvr.Start(m_Settings);
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
void CTcpIpSettingsPanel::OnPortNumberChanged( const QString& text )
{
    bool    bValid;
    int     PortValue = text.toInt(&bValid);

    ui->m_btnStartStop->setEnabled(bValid && PortValue >= 0 && PortValue <= 65535);
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

    if ( TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr().IsRunning() )
    {
        ui->m_btnStartStop->setIcon(StopIcon);
        ui->m_editTcpIpPortNumber->setEnabled(false);
        m_Settings = TraceClientCore::CModule::Instance().TcpModule().TcpTracesReceiversSvr().Settings();
    }
    else
    {
        ui->m_btnStartStop->setIcon(StartIcon);
        ui->m_editTcpIpPortNumber->setEnabled(true);
    }

    ui->m_btnStartStop->setEnabled(true);
}

