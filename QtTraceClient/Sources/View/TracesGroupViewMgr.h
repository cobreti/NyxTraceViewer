#ifndef TRACESGROUPVIEWMGR_H
#define TRACESGROUPVIEWMGR_H

#include "TracesGroup.hpp"
#include "TracesGroupView.h"

#include <map>

class CTracesGroupViewMgr
{
public:
    CTracesGroupViewMgr();
    virtual ~CTracesGroupViewMgr();

    CTracesGroupView* Get(TraceClientCore::TracesGroupId id);

protected:

    typedef     std::map<TraceClientCore::TracesGroupId, CTracesGroupView*>      TracesGroupViewMap;

protected:

    TracesGroupViewMap          m_TracesGroupViews;
};

#endif // TRACESGROUPVIEWMGR_H
