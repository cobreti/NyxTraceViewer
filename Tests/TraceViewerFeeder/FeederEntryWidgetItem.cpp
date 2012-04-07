#include "FeederEntryWidgetItem.hpp"


/**
 *
 */
CFeederEntryWidgetItem::CFeederEntryWidgetItem(const QString& text) :
QListWidgetItem(text)
{
}


/**
 *
 */
CFeederEntryWidgetItem::~CFeederEntryWidgetItem()
{
}


/**
 *
 */
CFeederEntry* CFeederEntryWidgetItem::GetFeederEntry() const
{
    return m_refFeederEntry;
}


/**
 *
 */
void CFeederEntryWidgetItem::SetFeederEntry( CFeederEntry* pEntry )
{
    m_refFeederEntry = pEntry;
}