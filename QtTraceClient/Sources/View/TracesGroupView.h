#ifndef TRACESGROUPVIEW_H
#define TRACESGROUPVIEW_H

#include <Nyx.hpp>

#include "Decorations/ViewTraceObjectsDirectory.h"
#include "Decorations/DynamicHighlightsDirectory.h"

#include <QtGui>


class CTracesGroupView : public Nyx::CRefCount_Impl<>
{
public:
    CTracesGroupView();
    virtual ~CTracesGroupView();

    CViewTraceObjectsDirectory&     SectionsHilights()  { return m_TraceSectionsHilights; }
    CDynamicHighlightsDirectory&    DynamicHilights() { return m_DynamicHighlights; }

    QString& FocusedText()          { return m_FocusedText; }

protected:
    CViewTraceObjectsDirectory          m_TraceSectionsHilights;
    CDynamicHighlightsDirectory         m_DynamicHighlights;
    QString                             m_FocusedText;
};

#endif // TRACESGROUPVIEW_H
