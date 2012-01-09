#ifndef _POOLTREEITEM_HPP_
#define _POOLTREEITEM_HPP_

#include <QTreeWidgetItem>

namespace TraceClientCore
{
	class CTracesPool;
    class CTraceChannel;
}


namespace MainWindow
{
	class CPoolTreeItem : public QTreeWidgetItem
	{
	public:
		CPoolTreeItem();
		virtual ~CPoolTreeItem();

        virtual void SetPool( TraceClientCore::CTracesPool* pPool );
        virtual void SetChannel( TraceClientCore::CTraceChannel* pChannel );

		TraceClientCore::CTracesPool*		TracesPool() const		{ return m_pTracesPool; }
        TraceClientCore::CTraceChannel*     TraceChannel() const    { return m_pChannel; }

	protected:

		TraceClientCore::CTracesPool*		m_pTracesPool;
        TraceClientCore::CTraceChannel*     m_pChannel;
	};
};

#endif // _POOLTREEITEM_HPP_
