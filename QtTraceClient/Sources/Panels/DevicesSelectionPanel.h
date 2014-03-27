#ifndef DEVICESSELECTIONPANEL_H
#define DEVICESSELECTIONPANEL_H

#include <QWidget>

namespace Ui
{
    class DevicesSelection;
}

class CDevicesSelectionPanel : public QWidget
{
    Q_OBJECT

public:
    CDevicesSelectionPanel();
    virtual ~CDevicesSelectionPanel();

public slots:

    void onDeviceNameChanged(const QString& text);
    void onAddDevice();
    void onFocusChanged( QWidget* pOld, QWidget* pNew );

signals:


protected:

    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

protected:

    Ui::DevicesSelection*       ui;
};

#endif // DEVICESSELECTIONPANEL_H
