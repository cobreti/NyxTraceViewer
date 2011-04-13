#ifndef DEBUGPANEL_H
#define DEBUGPANEL_H

#include <QWidget>

namespace Ui
{
    class CDebugPanel;
}

class CDebugPanel : public QWidget
{
    Q_OBJECT

public:
    CDebugPanel(QWidget* parent);
    virtual ~CDebugPanel();

public slots:

    void OnInsertTraces();
    void OnEnumTraces();

signals:

protected:

    virtual void closeEvent(QCloseEvent* event);

private:

    Ui::CDebugPanel*        ui;
};

#endif // CDEBUGPANEL_H
