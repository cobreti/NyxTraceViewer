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
    
signals:
    
    void TcpReceiversStateChanged();

public slots:

    void OnStartStop();
    void OnTcpReceiversStateChanged();
    
protected:

    virtual void showEvent(QShowEvent *);

    void UpdateStartStopButtons();

protected:

    Ui::TcpIpSettingsPanel*     ui;

    TraceClientCore::CTcpTracesReceivers::CSettings     m_Settings;
};

#endif // TCPIPSETTINGSPANEL_H