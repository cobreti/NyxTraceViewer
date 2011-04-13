#include "PoolTreeItem.hpp"
#include "TracesPool.hpp"

namespace MainWindow
{
	/**
	 *
	 */
	CPoolTreeItem::CPoolTreeItem() : QTreeWidgetItem(Qt::ItemIsUserCheckable),
		m_pTracesPool(NULL)
	{
		setCheckState(0, Qt::Unchecked);
	}

	/**
	 *
	 */
	CPoolTreeItem::~CPoolTreeItem()
	{
	}

	/**
	 *
	 */
	void CPoolTreeItem::SetPool( TraceClientCore::CTracesPool* pPool )
	{
		m_pTracesPool = pPool;

		QString		text = QString().fromWCharArray(pPool->Name().c_str());
		QString		desc = QString().fromWCharArray(pPool->getDescription().c_str());

		setText(0, text);
		setText(1, desc);
	}
}

