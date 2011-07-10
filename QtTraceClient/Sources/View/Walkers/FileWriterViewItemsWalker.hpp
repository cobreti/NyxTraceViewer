#ifndef __FILEWRITERVIEWITEMSWALKER_HPP__
#define __FILEWRITERVIEWITEMSWALKER_HPP__

#include "ViewItemsWalker.hpp"

class QFile;

class CFileWriterViewItemsWalker : public CViewItemsWalker
{
public:
    CFileWriterViewItemsWalker(const CViewItemsWalker& walker);

    void Write(QFile& file);
};

#endif // FILEWRITERVIEWITEMSWALKER_HPP
