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

    void show( CTracesView* pView );
    void hide();
    void DetachView( CTracesView* pView );

public slots:

    void OnShowHideSettings( ViewEnums::ESettings settings, bool bShow );
    void OnPin(bool bPinned );
    void OnSave();

protected:

    void closeEvent( QCloseEvent* );

protected:
    Ui::ViewPage*               ui;
    CTracesView*                m_pView;
    CSettingsToolBar*           m_pTBSettings;
    QHBoxLayout*                m_pTBArea;
    QVBoxLayout*                m_pViewLayout;
    CPipesMgntPage*             m_pPipesMgntPage;
};


#endif // _VIEWPAGE_HPP_

