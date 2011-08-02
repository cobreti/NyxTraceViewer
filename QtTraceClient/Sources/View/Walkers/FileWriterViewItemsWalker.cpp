#include "FileWriterViewItemsWalker.hpp"
#include "../ViewItem_TraceData.hpp"

#include <QFile>

/**
 *
 */
CFileWriterViewItemsWalker::CFileWriterViewItemsWalker(const CViewItemsWalker& walker) :
    CViewItemsWalker(walker),
    m_ModuleNameWidth(0),
    m_TickCountWidth(0),
    m_ThreadIdWidth(0),
    m_ColumnsSpacing(3)
{
}


/**
 *
 */
void CFileWriterViewItemsWalker::Write(Nyx::CAnsiFileRef refFile)
{
    CalculateColumnsWidth();
    WriteItems(refFile);
}


/**
 *
 */
void CFileWriterViewItemsWalker::CalculateColumnsWidth()
{
    if ( !MoveToBegin() )
        return;

    while (1)
    {
        CViewItem_TraceData*        pItem = static_cast<CViewItem_TraceData*>(Item());

        if ( pItem )
        {
            m_ModuleNameWidth = Nyx::Max( m_ModuleNameWidth, pItem->ModuleName().length());
            m_TickCountWidth = Nyx::Max( m_TickCountWidth, pItem->TraceData()->TickCount().length());

            if ( pItem->TraceData()->Type() == TraceClientCore::CTraceData::eTT_User )
                m_ThreadIdWidth = Nyx::Max( m_ThreadIdWidth, pItem->TraceData()->ThreadId().length());
        }

        if ( !MoveToNext())
            return;
    }
}


/**
 *
 */
void CFileWriterViewItemsWalker::WriteItems(Nyx::CAnsiFileRef refFile)
{
    if ( !MoveToBegin() )
        return;

    while (1)
    {
        CViewItem_TraceData*        pItem = static_cast<CViewItem_TraceData*>(Item());

        if ( pItem )
        {
            refFile->Write( pItem->ModuleName());
            WriteSpaces( refFile, m_ModuleNameWidth - pItem->ModuleName().length() );
            WriteSpaces( refFile, m_ColumnsSpacing );

            refFile->Write( pItem->TraceData()->TickCount());
            WriteSpaces( refFile, m_TickCountWidth - pItem->TraceData()->TickCount().length());
            WriteSpaces( refFile, m_ColumnsSpacing );

            if ( pItem->TraceData()->Type() == TraceClientCore::CTraceData::eTT_User )
            {
                refFile->Write( pItem->TraceData()->ThreadId());
                WriteSpaces( refFile, m_ThreadIdWidth - pItem->TraceData()->ThreadId().length());
            }
            else
                WriteSpaces( refFile, m_ThreadIdWidth );

            WriteSpaces( refFile, m_ColumnsSpacing );
            WriteData( refFile, pItem );
        }

        if ( !MoveToNext())
            return;
    }
}


/**
 *
 */
void CFileWriterViewItemsWalker::WriteData(Nyx::CAnsiFileRef refFile, CViewItem_TraceData* pItem)
{
    m_AnsiBuffer = pItem->TraceData()->Data();

    char*       ptr = m_AnsiBuffer.BufferPtr();
    size_t      len = 0;
    char*       p = ptr;
    size_t      indent = m_ModuleNameWidth + m_ColumnsSpacing + m_TickCountWidth + m_ColumnsSpacing + m_ThreadIdWidth + m_ColumnsSpacing;
    
    for (len = 0; !(*p < 0x20); ++p, ++len);

    if ( len > 0 )
        refFile->Write(ptr, len);

    while ( *p != 0 )
    {
        for ( ; *p < 0x20; ++p );
        for ( ptr = p, len = 0; !(*p < 0x20); ++p, ++len);

        if ( len > 0 )
        {
            refFile->WriteEOL();
            WriteSpaces(refFile, indent);
            refFile->Write(ptr, len);
        }
    }

    //refFile->Write( m_AnsiBuffer );
    refFile->WriteEOL();
}


/**
 *
 */
void CFileWriterViewItemsWalker::WriteSpaces(Nyx::CAnsiFileRef refFile, size_t size)
{
    Nyx::CAString               space(" ");

    while ( size-- > 0 )
        refFile->Write( space );
}
