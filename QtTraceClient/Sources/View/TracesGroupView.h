#ifndef TRACESGROUPVIEW_H
#define TRACESGROUPVIEW_H

#include <Nyx.hpp>

#include "Decorations/ViewTraceObjectsDirectory.h"
#include "Decorations/DynamicHighlightsDirectory.h"
#include "ViewColumnsSettings.hpp"


#include <QtGui>


class CTracesGroupView : public Nyx::CRefCount_Impl<>
{
public:
    CTracesGroupView();
    virtual ~CTracesGroupView();

    CViewTraceObjectsDirectory&     SectionsHilights()  { return m_TraceSectionsHilights; }
    CDynamicHighlightsDirectory&    DynamicHilights() { return m_DynamicHighlights; }

    QString& FocusedText()          { return m_FocusedText; }

    bool KeepAtEnd() const          { return m_bKeepAtEnd; }
    bool& KeepAtEnd()               { return m_bKeepAtEnd; }

    const CViewColumnsSettings&     ColumnsSettings() const { return m_ColumnsSettings; }
    CViewColumnsSettings&           ColumnsSettings()       { return m_ColumnsSettings; }

protected:
    CViewTraceObjectsDirectory          m_TraceSectionsHilights;
    CDynamicHighlightsDirectory         m_DynamicHighlights;
    QString                             m_FocusedText;
    bool                                m_bKeepAtEnd;
    CViewColumnsSettings                m_ColumnsSettings;
};

#endif // TRACESGROUPVIEW_H
