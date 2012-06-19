#ifndef CCLEARCHANNELCONTENTCONFIRMATIONDLG_HPP
#define CCLEARCHANNELCONTENTCONFIRMATIONDLG_HPP

#include <QDialog>

/**
 *
 */
namespace Ui {
class CClearChannelContentConfirmationDlg;
}


/**
 *
 */
class CClearChannelContentConfirmationDlg : public QDialog
{
    Q_OBJECT

public:

    enum EDlgResult
    {
        eDlgRes_Empty,
        eDlgRes_Cancel
    };

public:
    explicit CClearChannelContentConfirmationDlg(const QString& channelName, QWidget *parent = 0);
    virtual ~CClearChannelContentConfirmationDlg();
    
    EDlgResult      Result() const      { return m_eDlgResult; }

private slots:

    void on_btnEmptyChannel_clicked();
    void on_btnCancel_clicked();

private:
    Ui::CClearChannelContentConfirmationDlg *ui;

    EDlgResult          m_eDlgResult;
};


#endif // CCLEARCHANNELCONTENTCONFIRMATIONDLG_HPP
