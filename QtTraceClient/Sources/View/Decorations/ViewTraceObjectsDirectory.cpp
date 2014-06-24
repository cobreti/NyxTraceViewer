#include "ViewTraceObjectsDirectory.h"

#include <Nyx.hpp>
#include <algorithm>


CViewTraceObjectsDirectory::CViewTraceObjectsDirectory()
{
}


CViewTraceObjectsDirectory::~CViewTraceObjectsDirectory()
{
    auto eachfct = [] ( std::pair<const CTraceSectionId, const CViewTraceObject*> pair ) { delete pair.second; };

    std::for_each( m_ObjectsTable.begin(), m_ObjectsTable.end(), eachfct );
}


void CViewTraceObjectsDirectory::Set(const CTraceSectionId &id, CViewTraceObject *pObject)
{
    if ( NULL == pObject )
        return;

    if ( m_ObjectsTable.count(id) > 0 )
    {
        CViewTraceObject*   pOldObject = m_ObjectsTable[id];
        delete pOldObject;
    }

    m_ObjectsTable[id] = pObject;
}


void CViewTraceObjectsDirectory::Remove(const CTraceSectionId &id)
{
    m_ObjectsTable.erase(id);
}


CViewTraceObject* CViewTraceObjectsDirectory::Get(const CTraceSectionId& id) const
{
    TViewTraceObjectsMap::const_iterator    pos = m_ObjectsTable.find(id);

    if ( pos != m_ObjectsTable.end() )
        return pos->second;

    return NULL;
}


void CViewTraceObjectsDirectory::enumContent()
{
    auto eachFct = [&] ( std::pair<const CTraceSectionId, const CViewTraceObject*> pair )
    {
        NYXTRACE( 0x0, L"    -- view trace object");
    };

//    NYXTRACE(0x0, L"begin enum content");

    std::for_each( m_ObjectsTable.begin(), m_ObjectsTable.end(), eachFct );

//    NYXTRACE(0x0, L"end enum content");
}
