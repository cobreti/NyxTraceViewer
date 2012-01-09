#include "PoolTreeItem.hpp"
#include "TracesPool.hpp"
#include "TraceChannel.hpp"

namespace MainWindow
{
	/**
	 *
	 */
	CPoolTreeItem::CPoolTreeItem() : QTreeWidgetItem(Qt::ItemIsUserCheckable),
        m_pTracesPool(NULL),
        m_pChannel(NULL)
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

    /**
     *
     */
    void CPoolTreeItem::SetChannel( TraceClientCore::CTraceChannel* pChannel )
    {
        m_pChannel = pChannel;

        QString     name = pChannel->Name().c_str();

        setText(0, name);
    }
}

