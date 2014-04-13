#ifndef VIEWTRACEPICKER_H
#define VIEWTRACEPICKER_H

#include "ViewTracesDisplayCache.h"

#include <QString>
#include <QRectF>
#include <map>

class CViewTracesDisplayCache;


class CViewTracePicker
{
public:

    class CPickerEntry : public CViewTracesDisplayCache::CEntryData
    {
    public:
        CPickerEntry() {}
        CPickerEntry(EViewColumnId columnId);
        CPickerEntry(const CPickerEntry& entry);
        CPickerEntry(const CViewTracesDisplayCache::CEntryData& entryData, EViewColumnId columnId);
        virtual ~CPickerEntry();

        const CPickerEntry& operator = (const CPickerEntry& entry);

        const EViewColumnId&    columnId() const            { return m_ColumnId; }
        EViewColumnId&          columnId()                  { return m_ColumnId; }

    protected:
        EViewColumnId           m_ColumnId;
    };

public:
    CViewTracePicker(const CViewTracesDisplayCache& rDisplayCache);
    virtual ~CViewTracePicker();

    virtual QString getTextInRect( const QRectF& rcArea );

protected:

    typedef     std::map<int, CPickerEntry>     TEntriesRow;
    typedef     std::map<int, TEntriesRow>      TEntriesTable;

protected:

    const CViewTracesDisplayCache&      m_rDisplayCache;

    TEntriesTable                       m_Entries;
};


#endif // VIEWTRACEPICKER_H
