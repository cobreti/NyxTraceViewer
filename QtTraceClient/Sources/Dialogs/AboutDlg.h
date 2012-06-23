#ifndef _ABOUTDLG_H_
#define _ABOUTDLG_H_

#include <QDialog>

namespace Ui
{
    class AboutDlg;
}


/**
 *
 */
class CAboutDlg : public QDialog
{
    Q_OBJECT
        
public:
    CAboutDlg(QWidget* parent);
    virtual ~CAboutDlg();

public slots:

    void OnClose();

protected:

    void paintEvent(QPaintEvent* pEvent);

protected:

    Ui::AboutDlg*       ui;
};


#endif // _ABOUTDLG_H_

