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

        const QString&          textInSelection() const     { return m_TextInSelection; }
        QString&                textInSelection()           { return m_TextInSelection; }

        const int&              startIndex() const          { return m_StartIndex; }
        int&                    startIndex()                { return m_StartIndex; }

        const int&              length() const              { return m_Length; }
        int&                    length()                    { return m_Length; }

        const QRectF&           subRect() const             { return m_SubRect; }
        QRectF&                 subRect()                   { return m_SubRect; }

    protected:
        EViewColumnId           m_ColumnId;
        QString                 m_TextInSelection;
        int                     m_StartIndex;
        int                     m_Length;
        QRectF                  m_SubRect;
    };


    class CPickerResult
    {
        friend class CViewTracePicker;

    public:
        CPickerResult();
        CPickerResult(CPickerResult&& result);
        virtual ~CPickerResult();

        template <class _FUNCTION>
        void for_each(_FUNCTION fct)
        {
            std::for_each( m_pEntries->begin(), m_pEntries->end(), [&] (std::pair<int, CPickerResult::TEntriesRow> pair)
                {
                    std::for_each( pair.second.begin(), pair.second.end(), [&] (std::pair<int, CPickerEntry> values)
                    {
                        fct(pair.first, values.first, values.second);
                    });
                });
        }

    protected:

        typedef     std::map<int, CPickerEntry>     TEntriesRow;
        typedef     std::map<int, TEntriesRow>      TEntriesTable;

        TEntriesTable*                       m_pEntries;

    private:

        CPickerResult(const CPickerResult&);
        const CPickerResult& operator = (const CPickerResult&);
    };


public:
    CViewTracePicker(const CViewTracesDisplayCache& rDisplayCache);
    virtual ~CViewTracePicker();

    virtual CPickerResult pick( const QRectF& rcArea );

protected:

    void ValidatePickEntry( const QRectF& rcArea,
                            const CTraceSectionId& id,
                            const CViewTracesDisplayCache::CEntryData& data,
                            CPickerResult& result);

protected:

    const CViewTracesDisplayCache&      m_rDisplayCache;

};


#endif // VIEWTRACEPICKER_H
