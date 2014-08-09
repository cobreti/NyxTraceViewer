#include <Nyx.hpp>

#include "TracesGroupListItem.h"


CTracesGroupListItem::CTracesGroupListItem(TraceClientCore::CTracesGroup* pGroup, QListWidget *pParent) : QListWidgetItem(pGroup->Name().c_str(), pParent, 0),
    m_pGroup(pGroup)
{

}


CTracesGroupListItem::~CTracesGroupListItem()
{

}

