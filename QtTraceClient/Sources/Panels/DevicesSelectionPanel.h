#ifndef DEVICESSELECTIONPANEL_H
#define DEVICESSELECTIONPANEL_H


#include "Device.h"

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

    virtual bool eventFilter(QObject *, QEvent *);

public slots:

    void onItemDoubleClicked( QTreeWidgetItem* pItem, int column );
    void onDeviceAdded(const CDevice& device);
    void onDeviceRemoved(const CDevice& device);
    void onDeviceMapped(int id);
    void onDeviceUnmapped(int id);

signals:

    void closing();

protected:


    class XTreeItem : public QTreeWidgetItem
    {
    public:
        XTreeItem(const CDevice& device);
        virtual ~XTreeItem();

        bool isSelected() const                 { return m_bSelected; }
        void setSelected(bool bSelected);

        const CDevice&      device() const      { return m_Device; }
        CDevice&            device()            { return m_Device; }

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
    void listDevices();
    void addDevice(const CDevice& device);

protected:

    Ui::DevicesSelection*       ui;
};

#endif // DEVICESSELECTIONPANEL_H
