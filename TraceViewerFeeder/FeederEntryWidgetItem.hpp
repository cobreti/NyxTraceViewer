#ifndef _FEEDERENTRYWIDGETITEM_HPP_
#define _FEEDERENTRYWIDGETITEM_HPP_

#include <QListWidget>
#include "FeederEntry.hpp"
#include "FeederSource_UserText.hpp"
#include "FeederSource_TextFile.hpp"

/**
 *
 */
class CFeederEntryWidgetItem : public QListWidgetItem
{
public:
    CFeederEntryWidgetItem(const QString& text);
    virtual ~CFeederEntryWidgetItem();

    CFeederEntry* GetFeederEntry() const;
    void SetFeederEntry( CFeederEntry* pFeederEntry );

    CFeederSource_UserText& GetUserTextFeeder()             { return m_UserTextFeeder; }
    CFeederSource_TextFile& GetTextFileFeeder()             { return m_TextFileFeeder; }

protected:

    CFeederEntryRef             m_refFeederEntry;
    CFeederSource_UserText      m_UserTextFeeder;
    CFeederSource_TextFile      m_TextFileFeeder;
};

#endif // _FEEDERENTRYWIDGETITEM_HPP_
