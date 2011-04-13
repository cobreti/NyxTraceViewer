#ifndef _FEEDERENTRYWIDGETITEM_HPP_
#define _FEEDERENTRYWIDGETITEM_HPP_

#include <QListWidget>
#include "FeederEntry.hpp"

class CFeederEntryWidgetItem : public QListWidgetItem
{
public:
    CFeederEntryWidgetItem(const QString& text);
    virtual ~CFeederEntryWidgetItem();

    CFeederEntry* GetFeederEntry() const;
    void SetFeederEntry( CFeederEntry* pFeederEntry );

protected:

    CFeederEntryRef     m_refFeederEntry;
};

#endif // _FEEDERENTRYWIDGETITEM_HPP_
