#ifndef VIEWTRACESCONTENTITERATOR_HPP
#define VIEWTRACESCONTENTITERATOR_HPP

#include "ViewTracesIterator.hpp"

#include "ViewColumnId.hpp"

#include <QString>



class CViewTracesContentIterator : public CViewTracesIterator
{
public:
    CViewTracesContentIterator();
    CViewTracesContentIterator(const CViewTracesContentIterator& iterator);
    virtual ~CViewTracesContentIterator();

    const CViewTracesContentIterator& operator = (const CViewTracesContentIterator& iterator);
    const CViewTracesContentIterator& operator = (const CViewTracesIterator& iterator);

    const EViewColumnId&            columnId() const            { return m_ColumnsOrder[m_ColumnIndex]; }
    int                             textIndex() const           { return m_TextIndex; }
    const QString&                  text() const                { return m_Text; }

    virtual void setText(const QString& text);
    virtual void setColumnsOrder(const ColumnsIdVector& columnsOrder);

    CViewTracesContentIterator& operator ++ ();
    CViewTracesContentIterator& operator -- ();

    void moveToEnd();

protected:

    int                     m_ColumnIndex;
    int                     m_TextIndex;
    QString                 m_Text;
    ColumnsIdVector         m_ColumnsOrder;
};


#endif // VIEWTRACESCONTENTITERATOR_HPP
