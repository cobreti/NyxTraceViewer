#include "CClearChannelContentConfirmationDlg.hpp"
#include "ui_CClearChannelContentConfirmationDlg.h"


/**
 *
 */
CClearChannelContentConfirmationDlg::CClearChannelContentConfirmationDlg(const QString& channelName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CClearChannelContentConfirmationDlg),
    m_eDlgResult(eDlgRes_Cancel)
{
    ui->setupUi(this);

    ui->labelChannelName->setText(channelName);
}


/**
 *
 */
CClearChannelContentConfirmationDlg::~CClearChannelContentConfirmationDlg()
{
    delete ui;
}


/**
 *
 */
void CClearChannelContentConfirmationDlg::on_btnEmptyChannel_clicked()
{
    m_eDlgResult = eDlgRes_Empty;
    close();
}


/**
 *
 */
void CClearChannelContentConfirmationDlg::on_btnCancel_clicked()
{
    close();
}
