#ifndef CCHANNELTREEITEM_HPP
#define CCHANNELTREEITEM_HPP

#include <QTreeWidgetItem>


namespace TraceClientCore
{
    class CTraceChannel;
}


/**
 *
 */
class CChannelTreeItem : public QTreeWidgetItem
{
public:
    CChannelTreeItem();
    virtual ~CChannelTreeItem();

    void SetChannel( TraceClientCore::CTraceChannel* pChannel );

    TraceClientCore::CTraceChannel*     TraceChannel() const    { return m_pChannel; }

protected:

    TraceClientCore::CTraceChannel*     m_pChannel;
};


#endif // CCHANNELTREEITEM_HPP
