#ifndef CHANNELSMGNT_HPP
#define CHANNELSMGNT_HPP

#include <QWidget>


class CChannelTreeItemDelegate;
class QTreeWidgetItem;
class CTracesViewCore;

namespace Ui
{
    class ChannelsMgnt;
}

namespace TraceClientCore
{
    class CTraceChannel;
}

class CChannelsMgnt : public QWidget
{
    Q_OBJECT
    
public:

    static void Show( QWidget* pParent, const QPoint& pt, CTracesViewCore* pViewCore = NULL );
    
public slots:

    void OnNewChannel();
    void OnChannelItemChanged( QTreeWidgetItem* pItem, int column );
    void OnChannelItemClicked( QTreeWidgetItem* pItem, int column );
    void OnChannelItemDoubleClicked( QTreeWidgetItem* pItem, int column );

signals:

//    void sigEmptyChannel(TraceClientCore::CTraceChannel* pChannel);

protected:

    explicit CChannelsMgnt();
    ~CChannelsMgnt();

    void Init( QWidget* pParent, const QPoint& pt, CTracesViewCore* pViewCore );
    void LoadChannels();

    void showEvent(QShowEvent *pEvent);

    void EmptyChannel(TraceClientCore::CTraceChannel* pChannel);

private:
    Ui::ChannelsMgnt *ui;

    CChannelTreeItemDelegate*   m_pChannelTreeItemDelegate;
    CTracesViewCore*            m_pViewCore;
    int                         m_NextChannelNumber;

    static CChannelsMgnt*       s_pInstance;
};

#endif // CHANNELSMGNT_HPP
