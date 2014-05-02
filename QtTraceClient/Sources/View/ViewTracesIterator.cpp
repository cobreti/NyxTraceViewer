//
//  ViewTracesIterator.cpp
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-22.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//


#include "ViewTracesIterator.hpp"
#include "TracesGroup.hpp"


/**
 *
 */
CViewTracesIterator CViewTracesIterator::FirstPos(TraceClientCore::CTracesGroup *pGroup)
{
    CViewTracesIterator     iter(pGroup);
    
    if ( NULL != pGroup && pGroup->LinesCount() > 0 )
    {
        iter.m_Pos = pGroup->FirstPos();
        iter.m_LineNumber = 0;
        iter.m_Initialized = true;
    }
    
    return iter;
}


/**
 *
 */
CViewTracesIterator CViewTracesIterator::LastPos(TraceClientCore::CTracesGroup *pGroup)
{
    CViewTracesIterator     iter(pGroup);

    if ( NULL != pGroup && pGroup->LinesCount() > 0 )
    {
        iter.m_Pos = pGroup->LastPos();
        iter.m_LineNumber = pGroup->LinesCount()-1;
        iter.m_Initialized = true;
    }

    return iter;
}



/**
 *
 */
CViewTracesIterator::CViewTracesIterator() :
m_pGroup(NULL),
m_LineNumber(0),
    m_Initialized(false)
{
    
}


/**
 *
 */
CViewTracesIterator::CViewTracesIterator( TraceClientCore::CTracesGroup* pGroup ) :
m_pGroup(pGroup),
m_LineNumber(0),
  m_Initialized(false)
{
    
}


/**
 *
 */
CViewTracesIterator::CViewTracesIterator( const CViewTracesIterator& iter ) :
m_pGroup(iter.m_pGroup),
m_LineNumber(iter.m_LineNumber),
m_Pos(iter.m_Pos),
  m_Initialized(iter.m_Initialized)
{
    
}


/**
 *
 */
CViewTracesIterator::~CViewTracesIterator()
{
    
}


/**
 *
 */
const CViewTracesIterator& CViewTracesIterator::operator = (const CViewTracesIterator& iter)
{
    m_pGroup = iter.m_pGroup;
    m_LineNumber = iter.m_LineNumber;
    m_Pos = iter.m_Pos;
    m_Initialized = iter.m_Initialized;
    
    return *this;
}


/**
 *
 */
CViewTracesIterator& CViewTracesIterator::operator ++ ()
{
    if ( Valid() )
    {
        ++ m_Pos;
        ++ m_LineNumber;
    }
    
    return *this;
}


/**
 *
 */
CViewTracesIterator& CViewTracesIterator::operator -- ()
{
    if ( Valid() && m_LineNumber > 0 )
    {
        -- m_Pos;
        -- m_LineNumber;
    }
    
    return *this;
}


/**
 *
 */
bool CViewTracesIterator::Valid() const
{
    return m_Initialized && m_Pos.Valid();
}


/**
 *
 */
CViewTracesIterator& CViewTracesIterator::MoveToLine(const Nyx::UInt32& lineNumber)
{
    while ( Valid() && m_LineNumber < lineNumber )
        ++ (*this);
    
    while ( Valid() && m_LineNumber > lineNumber )
        -- (*this);

    return *this;
}


TraceClientCore::CTraceData* CViewTracesIterator::TraceData() const
{
    if ( !Valid() )
        return NULL;
    
    return m_Pos.TraceData();
}
