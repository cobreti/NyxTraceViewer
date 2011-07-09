#ifndef _VIEWPAGE_HPP_
#define _VIEWPAGE_HPP_

#include <QDialog>
#include <QFrame>
#include <QHBoxLayout>
#include <QToolButton>
#include "View/SettingsToolBar.hpp"


class CTracesView;
class CPipesMgntPage;

namespace Ui
{
    class ViewPage;
};


class CViewPage : public QDialog
{
    Q_OBJECT

public:
    CViewPage( QWidget* pParent );
    virtual ~CViewPage();

    //QFrame* ViewFrame() const;

    void show( CTracesView* pView );
    void hide();
    void DetachView( CTracesView* pView );

public slots:

    void OnShowHideSettings( ViewEnums::ESettings settings, bool bShow );
    void OnPinBtnClicked( bool checked );

protected:

    void closeEvent( QCloseEvent* );

protected:
    Ui::ViewPage*               ui;
    CTracesView*                m_pView;
    CSettingsToolBar*           m_pTBSettings;
    QHBoxLayout*                m_pTBArea;
    QToolButton*                m_pBtnPin;
    CPipesMgntPage*             m_pPipesMgntPage;
};


#endif // _VIEWPAGE_HPP_

