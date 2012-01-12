#ifndef _POOLTREEITEM_HPP_
#define _POOLTREEITEM_HPP_

#include <QTreeWidgetItem>

namespace TraceClientCore
{
    class CTraceChannel;
}


namespace MainWindow
{
	class CPoolTreeItem : public QTreeWidgetItem
	{
	public:
		CPoolTreeItem();
		virtual ~CPoolTreeItem();

        virtual void SetChannel( TraceClientCore::CTraceChannel* pChannel );

        TraceClientCore::CTraceChannel*     TraceChannel() const    { return m_pChannel; }

	protected:

        TraceClientCore::CTraceChannel*     m_pChannel;
	};
};

#endif // _POOLTREEITEM_HPP_
