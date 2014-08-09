#ifndef CCHANNELSELECTION_H
#define CCHANNELSELECTION_H

#include "ChannelsListener.h"
#include "TracesGroupMgrListener.h"

#include <QWidget>

namespace Ui
{
    class ChannelSelection;
}


class CChannelSelection : public QWidget
{
    Q_OBJECT

public:
    CChannelSelection(QWidget* pParent);
    virtual ~CChannelSelection();

public slots:

    void onChannelSelectionChanged();
    void onNewChannel(TraceClientCore::CTraceChannel* pChannel);
    void onNewTracesGroup(TraceClientCore::CTracesGroup* pGroup);

signals:

    void SelectionChanged(TraceClientCore::CTracesGroup* pGroup);

protected:

    Ui::ChannelSelection*       ui;
    CChannelsListener           m_ChannelsListener;
    CTracesGroupMgrListener     m_TracesGroupListener;

};

#endif // CCHANNELSELECTION_H
