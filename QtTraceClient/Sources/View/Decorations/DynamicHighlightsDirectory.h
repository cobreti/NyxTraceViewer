#ifndef DYNAMICHIGHLIGHTSDIRECTORY_H
#define DYNAMICHIGHLIGHTSDIRECTORY_H


#include "DynamicHighlight.h"

#include <map>


class CDynamicHighlightsDirectory
{
public:
    CDynamicHighlightsDirectory();
    virtual ~CDynamicHighlightsDirectory();

    virtual void Add( CDynamicHighlight* pHighlight );
    virtual void Remove( const CDynamicHighlight::ID& id );
    virtual CDynamicHighlight* Get( const CDynamicHighlight::ID& id );

    virtual void Draw( CViewTracePainter::CPaintContext& context ) const;

protected:

    typedef     std::map<CDynamicHighlight::ID, CDynamicHighlight*>             HighlightsTable;


protected:

    HighlightsTable         m_Highlights;
};


#endif // DYNAMICHIGHLIGHTSDIRECTORY_H
