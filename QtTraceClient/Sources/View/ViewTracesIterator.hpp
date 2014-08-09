//
//  ViewTracesIterator.hpp
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-22.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#ifndef NyxTraceViewer_ViewTracesIterator_hpp
#define NyxTraceViewer_ViewTracesIterator_hpp

#include <Nyx.hpp>
#include "MultiViewTracesIterator.hpp"


namespace TraceClientCore
{
    class CTracesGroup;
    class CTraceData;
}


class CViewTracesIterator
{
public:
    
    static CViewTracesIterator FirstPos(TraceClientCore::CTracesGroup* pGroup);
    static CViewTracesIterator LastPos(TraceClientCore::CTracesGroup* pGroup);
    
public:
    CViewTracesIterator();
    CViewTracesIterator( TraceClientCore::CTracesGroup* pGroup );
    CViewTracesIterator(const CViewTracesIterator& iter);
    virtual ~CViewTracesIterator();
    
    const CViewTracesIterator& operator = (const CViewTracesIterator& iter);
    
    CViewTracesIterator& operator ++ ();
    CViewTracesIterator& operator -- ();
    
    bool Valid() const;
    
    CViewTracesIterator& MoveToLine( const Nyx::UInt32& lineNumber );
    
    TraceClientCore::CTraceData* TraceData() const;
    
    const Nyx::UInt32&      getLineNumber() const           { return m_LineNumber; }
    
protected:
    
    TraceClientCore::CTracesGroup*                  m_pGroup;
    Nyx::UInt32                                     m_LineNumber;
    TraceClientCore::CMultiViewTracesIterator       m_Pos;
    bool                                            m_Initialized;
};



#endif
