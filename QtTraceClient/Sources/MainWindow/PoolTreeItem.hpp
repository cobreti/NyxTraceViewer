#ifndef _POOLTREEITEM_HPP_
#define _POOLTREEITEM_HPP_

#include <QTreeWidgetItem>

namespace TraceClientCore
{
	class CTracesPool;
}


namespace MainWindow
{
	class CPoolTreeItem : public QTreeWidgetItem
	{
	public:
		CPoolTreeItem();
		virtual ~CPoolTreeItem();

		virtual void SetPool( TraceClientCore::CTracesPool* pPool );

		TraceClientCore::CTracesPool*		TracesPool() const		{ return m_pTracesPool; }

	protected:

		TraceClientCore::CTracesPool*		m_pTracesPool;
	};
};

#endif // _POOLTREEITEM_HPP_
