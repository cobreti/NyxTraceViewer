#ifndef __FILEWRITERVIEWITEMSWALKER_HPP__
#define __FILEWRITERVIEWITEMSWALKER_HPP__

#include <NyxAnsiFile.hpp>

#include "ViewItemsWalker.hpp"

class CViewItem_TraceData;

/**
 *
 */
class CFileWriterViewItemsWalker : public CViewItemsWalker
{
public:
    CFileWriterViewItemsWalker(const CViewItemsWalker& walker);

    void Write(Nyx::CAnsiFileRef refFile);

protected:

    void CalculateColumnsWidth();
    void WriteItems(Nyx::CAnsiFileRef refFile);
    void WriteData(Nyx::CAnsiFileRef refFile, CViewItem_TraceData* pItem);
    void WriteSpaces(Nyx::CAnsiFileRef refFile, size_t size );

protected:

    size_t              m_ModuleNameWidth;
    size_t              m_TickCountWidth;
    size_t              m_ThreadIdWidth;
    size_t              m_ColumnsSpacing;

    Nyx::CAString       m_AnsiBuffer;
};

#endif // FILEWRITERVIEWITEMSWALKER_HPP
