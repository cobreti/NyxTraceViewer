#include <Nyx.hpp>

#include "TracesGroupListItem.h"


CTracesGroupListItem::CTracesGroupListItem(TraceClientCore::CTracesGroup* pGroup, QListWidget *pParent) : QListWidgetItem(pGroup->Name(), pParent, 0),
    m_pGroup(pGroup)
{

}


CTracesGroupListItem::~CTracesGroupListItem()
{

}

