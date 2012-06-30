#include "TraceClientApp.h"

#include "ui_AboutDlg.h"

#include "AboutDlg.h"
#include <QtGui>

/**
 *
 */
CAboutDlg::CAboutDlg(QWidget* parent) : QDialog(parent),
    ui( new Ui::AboutDlg)
{
    ui->setupUi(this);

    connect( ui->CloseBtn, SIGNAL(clicked()), this, SLOT(OnClose()));

    QString     version = "v";
    version += CTraceClientApp::Instance().GetVersion();
    ui->labelVersion->setText(version);

}


/**
 *
 */
CAboutDlg::~CAboutDlg()
{
}


/**
 *
 */
void CAboutDlg::OnClose()
{
    close();
}


/**
 *
 */
void CAboutDlg::paintEvent(QPaintEvent* pEvent)
{
    QRect       rcArea;
    QIcon       AppIcon("://App/TraceViewer");
    QPainter    painter(this);

    rcArea = ui->AppIconWidget->geometry();
    AppIcon.paint(&painter, rcArea);
}
