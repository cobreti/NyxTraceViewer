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

    void enumContent();

protected:

    typedef     std::map<CTraceSectionId, CViewTraceObject*>        TViewTraceObjectsMap;

protected:

    TViewTraceObjectsMap        m_ObjectsTable;
};

#endif // VIEWTRACEOBJECTSDIRECTORY_H
