#ifndef SETTINGSPANEL_H
#define SETTINGSPANEL_H

#include <QWidget>

namespace Ui
{
    class SettingsPanel;
}


class CTcpIpSettingsPanel;


class CSettingsPanel : public QWidget
{
    Q_OBJECT

public:
    CSettingsPanel();
    virtual ~CSettingsPanel();

public slots:

    void onTraceDirectoryServerChanged(const QString& text);

signals:


protected:

    void Init();

protected:

    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

protected:

    Ui::SettingsPanel*      ui;

    CTcpIpSettingsPanel*        m_pTxtTcpIpSettingsPanel;
};


#endif // SETTINGSPANEL_H
