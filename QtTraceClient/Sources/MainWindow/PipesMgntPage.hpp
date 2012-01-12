#ifndef _PIPESMGNTPAGE_HPP_
#define _PIPESMGNTPAGE_HPP_

#include <QDialog>

class QTreeWidgetItem;
class CTracesDocument;

namespace Ui
{
    class PipesMgntPage;
};

class CPipesMgntPage : public QDialog
{
    Q_OBJECT
        
public:
    CPipesMgntPage( QWidget* pParent );

    void show(CTracesDocument* pDoc);
    void Refresh();

public slots:

    void OnNewPool();
    void OnStartStop();
    void OnPoolSelectionChanged();
    void OnPoolItemChanged( QTreeWidgetItem* pItem, int column );
    void OnPoolItemClicked( QTreeWidgetItem* pItem, int column );

protected:

    void FillPoolsList();

protected:

    Ui::PipesMgntPage*          ui;
    CTracesDocument*            m_pDoc;
};

#endif // _PIPESMGNTPAGE_HPP_
