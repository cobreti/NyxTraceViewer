#ifndef DYNAMICHIGHLIGHT_H
#define DYNAMICHIGHLIGHT_H

#include "../ViewColumnId.hpp"
#include "../ViewTracePainter.h"


class CDynamicHighlight
{
public:
    typedef     int         ID;

    enum
    {
        kDefault        = 1,
        kFocusedItem    = 2,
        kBatchStart     = 100
    };

public:
    CDynamicHighlight();
    virtual ~CDynamicHighlight();

    const ID&       id() const          { return m_Id; }
    ID&             id()                { return m_Id; }


    virtual void Draw( CViewTracePainter::CPaintContext& context );

protected:

    ID          m_Id;


private:
    CDynamicHighlight(const CDynamicHighlight&);
    const CDynamicHighlight& operator = (const CDynamicHighlight&);

};

#endif // DYNAMICHIGHLIGHT_H
