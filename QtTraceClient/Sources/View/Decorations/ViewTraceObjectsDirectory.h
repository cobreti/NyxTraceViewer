#ifndef VIEWTRACEOBJECTSDIRECTORY_H
#define VIEWTRACEOBJECTSDIRECTORY_H


#include "../TraceSectionId.h"

#include <map>

class CViewTraceObject;

class CViewTraceObjectsDirectory
{
public:
    CViewTraceObjectsDirectory();
    virtual ~CViewTraceObjectsDirectory();

    void Set( const CTraceSectionId& id, CViewTraceObject* pObject );
    void Remove( const CTraceSectionId& id );
    CViewTraceObject* Get(const CTraceSectionId& id) const;

    void Clear();

    void enumContent();

    void ImportFrom( CViewTraceObjectsDirectory& directory );

protected:

    typedef     std::map<CTraceSectionId, CViewTraceObject*>        TViewTraceObjectsMap;

protected:

    TViewTraceObjectsMap        m_ObjectsTable;
};


#endif // VIEWTRACEOBJECTSDIRECTORY_H
