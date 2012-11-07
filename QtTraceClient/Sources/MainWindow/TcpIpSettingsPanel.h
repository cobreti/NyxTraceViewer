#ifndef TCPIPSETTINGSPANEL_H
#define TCPIPSETTINGSPANEL_H

#include "TraceClientCoreModule.hpp"

#include <QWidget>

namespace Ui
{
    class TcpIpSettingsPanel;
}

/**
 *
 */
class CTcpIpSettingsPanel : public QWidget
{
    Q_OBJECT

    friend class CReceiversListenerBridge;

public:
    explicit CTcpIpSettingsPanel(QWidget *parent = 0);

    void SetTracesReceiversSvr( TraceClientCore::CTcpTracesReceiversSvr* pSvr );

signals:
    
    void TcpReceiversStateChanged();

public slots:

    void OnStartStop();
    void OnTcpReceiversStateChanged();
    void OnPortNumberChanged( const QString& text );
    
protected:

    virtual void showEvent(QShowEvent *);

    void UpdateStartStopButtons();

protected:

    Ui::TcpIpSettingsPanel*     ui;

    TraceClientCore::CTcpTracesReceiversSvr*                m_pReceiversSvr;
    TraceClientCore::CTcpTracesReceiversSvr::CSettings      m_Settings;
};

#endif // TCPIPSETTINGSPANEL_H
