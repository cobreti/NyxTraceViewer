#ifndef TRACESGROUPVIEW_H
#define TRACESGROUPVIEW_H

#include <Nyx.hpp>

#include "Decorations/ViewTraceObjectsDirectory.h"


class CTracesGroupView : public Nyx::CRefCount_Impl<>
{
public:
    CTracesGroupView();
    virtual ~CTracesGroupView();

    CViewTraceObjectsDirectory&     SectionsHilights()  { return m_TraceSectionsHilights; }

protected:
    CViewTraceObjectsDirectory          m_TraceSectionsHilights;
};

#endif // TRACESGROUPVIEW_H
