//
//  TracesIterator.cpp
//  TraceClientCore
//
//  Created by Danny Thibaudeau on 2013-09-20.
//
//

#include "TracesIterator.hpp"


namespace TraceClientCore
{
    /**
     *
     */
    CTracesIterator::CTracesIterator() :
    m_pList(NULL)
    {
        
    }
    
    
    /**
     *
     */
    CTracesIterator::CTracesIterator( CTracesList* pList ) :
    m_pList(pList)
    {
        Nyx::TMutexLock     tracesLock(m_pList->m_refMutex, true);
        
        m_Pos = m_pList->end();
    }
    
    
    /**
     *
     */
    CTracesIterator::CTracesIterator( CTracesList* pList, const CTracesList::iterator& pos ) :
    m_pList(pList),
    m_Pos(pos)
    {
        
    }

    
    /**
     *
     */
    CTracesIterator::CTracesIterator( const CTracesIterator& iter ) :
    m_pList(iter.m_pList),
    m_Pos(iter.m_Pos)
    {
    }
    
    /**
     *
     */
    CTracesIterator::~CTracesIterator()
    {
        
    }
    
    
    /**
     *
     */
    const CTracesIterator& CTracesIterator::operator = (const CTracesIterator& iter)
    {
        m_pList = iter.m_pList;
        m_Pos = iter.m_Pos;
        
        return *this;
    }
    
    
    /**
     *
     */
    const CTracesIterator& CTracesIterator::operator ++ ()
    {
        if ( m_pList != NULL )
        {
            Nyx::TMutexLock     lock(m_pList->m_refMutex, true);
            
            ++ m_Pos;
            
            if ( m_Pos == m_pList->end() )
            {
                m_pList = NULL;
            }
        }
        
        return *this;
    }
    
    
    /**
     *
     */
    const CTracesIterator& CTracesIterator::operator -- ()
    {
        if ( m_pList != NULL )
        {
            Nyx::TMutexLock     lock(m_pList->m_refMutex, true);
            
            if ( m_Pos == m_pList->begin() )
            {
                m_pList = NULL;
            }
            else
            {
                -- m_Pos;
            }
        }

        return *this;
    }
    
    
    /**
     *
     */
    bool CTracesIterator::Valid() const
    {
        return (m_pList != NULL);
    }
    
    
    /**
     *
     */
    CTraceData* CTracesIterator::TraceData() const
    {
        if ( m_pList != NULL )
            return *m_Pos;
        
        return NULL;
    }
}

