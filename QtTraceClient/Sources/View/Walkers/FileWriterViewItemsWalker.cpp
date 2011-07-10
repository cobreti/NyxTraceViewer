#include "FileWriterViewItemsWalker.hpp"
#include "../ViewItem_TraceData.hpp"

#include <QFile>

/**
 *
 */
CFileWriterViewItemsWalker::CFileWriterViewItemsWalker(const CViewItemsWalker& walker) :
    CViewItemsWalker(walker)
{
}


/**
 *
 */
void CFileWriterViewItemsWalker::Write(QFile& file)
{
    if ( !MoveToBegin() )
        return;

    while (1)
    {
        CViewItem_TraceData*        pItem = static_cast<CViewItem_TraceData*>(ItemPos().Item());

        if ( pItem )
        {
        }

        if ( !MoveToNext())
            return;
    }
}

