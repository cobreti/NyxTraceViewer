#ifndef DEVICESSELECTIONPANEL_H
#define DEVICESSELECTIONPANEL_H


#include "device.h"

#include <QWidget>
#include <QItemDelegate>
#include <QTreeWidgetItem>


namespace Ui
{
    class DevicesSelection;
}

class CDevicesSelectionPanel : public QWidget
{
    Q_OBJECT

public:
    CDevicesSelectionPanel();
    virtual ~CDevicesSelectionPanel();

public slots:

    void onItemDoubleClicked( QTreeWidgetItem* pItem, int column );
    void onDeviceAdded(const CDevice& device);
    void onDeviceRemoved(const CDevice& device);

signals:


protected:


    class XTreeItem : public QTreeWidgetItem
    {
    public:
        XTreeItem(const CDevice& device);
        virtual ~XTreeItem();

        bool isSelected() const                 { return m_bSelected; }
        void setSelected(bool bSelected);

    protected:

        CDevice     m_Device;
        bool        m_bSelected;
    };



    class XItemDelegate : public QItemDelegate
    {
    public:
        XItemDelegate();
        virtual ~XItemDelegate();

        virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    protected:

        QIcon       m_CheckIcon;
    };

protected:

    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

protected:

    Ui::DevicesSelection*       ui;
};

#endif // DEVICESSELECTIONPANEL_H
