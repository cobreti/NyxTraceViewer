#ifndef _PIPESMGNTPAGE_HPP_
#define _PIPESMGNTPAGE_HPP_


#include <QDialog>


class QTreeWidgetItem;
class CPipesMgntPageItemDelegate;
class CTracesViewCore;

namespace Ui
{
    class PipesMgntPage;
};

class CPipesMgntPage : public QDialog
{
    Q_OBJECT
        
public:
    CPipesMgntPage( QWidget* pParent );
    virtual ~CPipesMgntPage();

    void show(CTracesViewCore* pViewCore);
    void Refresh();

public slots:

    void OnNewPool();
    void OnPoolItemChanged( QTreeWidgetItem* pItem, int column );
    void OnPoolItemClicked( QTreeWidgetItem* pItem, int column );
    void OnPoolItemDoubleClicked( QTreeWidgetItem* pItem, int column );

protected:

    void FillPoolsList();

protected:

    Ui::PipesMgntPage*              ui;
    CTracesViewCore*                m_pViewCore;
    CPipesMgntPageItemDelegate*     m_pItemDelegate;
};

#endif // _PIPESMGNTPAGE_HPP_
