#ifndef _VIEWPAGE_HPP_
#define _VIEWPAGE_HPP_

#include <QDialog>
#include <QFrame>


class CTracesView;

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

protected:
    Ui::ViewPage*       ui;
    CTracesView*        m_pView;
};


#endif // _VIEWPAGE_HPP_

