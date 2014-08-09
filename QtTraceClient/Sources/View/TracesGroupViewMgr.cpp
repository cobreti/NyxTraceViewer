#include "TracesGroupViewMgr.h"


CTracesGroupViewMgr::CTracesGroupViewMgr()
{
}


CTracesGroupViewMgr::~CTracesGroupViewMgr()
{
}



CTracesGroupView* CTracesGroupViewMgr::Get(TraceClientCore::TracesGroupId id)
{
    TracesGroupViewMap::const_iterator      pos = m_TracesGroupViews.find(id);
    CTracesGroupView*       pTGV = NULL;

    if ( pos == m_TracesGroupViews.end() )
    {
        pTGV = new CTracesGroupView();
        m_TracesGroupViews.insert( std::make_pair(id, pTGV) );
    }
    else
    {
        pTGV = pos->second;
    }

    return pTGV;
}
