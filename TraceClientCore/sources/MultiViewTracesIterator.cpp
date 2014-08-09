//
//  MultiViewTracesIterator.c
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-20.
//
//

#include "MultiViewTracesIterator.hpp"


namespace TraceClientCore
{
    /**
     *
     */
    CMultiViewTracesIterator::CMultiViewTracesIterator() :
    m_pCurrentView(NULL),
    m_pTracesGroup(NULL)
    {
        
    }
    
    
    /**
     *
     */
    CMultiViewTracesIterator::CMultiViewTracesIterator( const CMultiViewTracesIterator& iter ) :
    m_CurrentPos(iter.m_CurrentPos),
    m_pCurrentView(iter.m_pCurrentView),
    m_pTracesGroup(iter.m_pTracesGroup)
    {
        m_Iterators = iter.m_Iterators;
    }
    
    
    /**
     *
     */
    CMultiViewTracesIterator::~CMultiViewTracesIterator()
    {
        
    }
    
    
    /**
     *
     */
    const CMultiViewTracesIterator& CMultiViewTracesIterator::operator = (const CMultiViewTracesIterator& iter)
    {
        m_CurrentPos = iter.m_CurrentPos;
        m_pCurrentView = iter.m_pCurrentView;
        m_pTracesGroup = iter.m_pTracesGroup;
        m_Iterators = iter.m_Iterators;
        
        return *this;
    }
    
    
    /**
     *
     */
    bool CMultiViewTracesIterator::Valid() const
    {
        return (m_pTracesGroup != NULL && m_pCurrentView != NULL && m_CurrentPos.Valid());
    }
    
    
    /**
     *
     */
    const CMultiViewTracesIterator& CMultiViewTracesIterator::operator ++ ()
    {
        ++ m_CurrentPos;
        
        return *this;
    }


    /**
     *
     */
    const CMultiViewTracesIterator& CMultiViewTracesIterator::operator -- ()
    {
        -- m_CurrentPos;
        
        return *this;
    }
    
    
    /**
     *
     */
    CTraceData* CMultiViewTracesIterator::TraceData() const
    {
        if ( Valid() )
            return m_CurrentPos.TraceData();
        
        return NULL;
    }
}



