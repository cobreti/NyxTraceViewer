#ifndef TRACESGROUPVIEW_H
#define TRACESGROUPVIEW_H

#include <Nyx.hpp>

#include "Decorations/DynamicHighlightsDirectory.h"
#include "ViewColumnsSettings.hpp"
#include "Decorations/StaticHighlights.hpp"


#include <QtGui>


class CTracesGroupView : public Nyx::CRefCount_Impl<>
{
public:
    CTracesGroupView();
    virtual ~CTracesGroupView();

    CStaticHighlights&              StaticHighlights()  { return m_StaticHighlights; }
    CDynamicHighlightsDirectory&    DynamicHilights() { return m_DynamicHighlights; }

    QString& FocusedText()          { return m_FocusedText; }

    bool KeepAtEnd() const          { return m_bKeepAtEnd; }
    bool& KeepAtEnd()               { return m_bKeepAtEnd; }

    const CViewColumnsSettings&     ColumnsSettings() const { return m_ColumnsSettings; }
    CViewColumnsSettings&           ColumnsSettings()       { return m_ColumnsSettings; }

protected:
    CStaticHighlights                   m_StaticHighlights;
    CDynamicHighlightsDirectory         m_DynamicHighlights;
    QString                             m_FocusedText;
    bool                                m_bKeepAtEnd;
    CViewColumnsSettings                m_ColumnsSettings;
};

#endif // TRACESGROUPVIEW_H
