#include "PoolTreeItem.hpp"
#include "TracesPool.hpp"
#include "TraceChannel.hpp"

namespace MainWindow
{
	/**
	 *
	 */
	CPoolTreeItem::CPoolTreeItem() : QTreeWidgetItem(Qt::ItemIsUserCheckable),
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
    void CPoolTreeItem::SetChannel( TraceClientCore::CTraceChannel* pChannel )
    {
        m_pChannel = pChannel;

//        QString     name = pChannel->Name().c_str();

        setText(3, pChannel->Name());
    }
}

