#include "RepositoryTraceInserter.hpp"
#include "TraceDataRepository.hpp"

namespace TraceClientCore
{
    /**
     *
     */
    CRepositoryTraceInserter::CRepositoryTraceInserter(CTraceDataRepository& rRepository) :
    m_rRepository(rRepository)
    {
    }
    
    
    /**
     *
     */
    CRepositoryTraceInserter::~CRepositoryTraceInserter()
    {
    }
    
    
    /**
     *
     */
    void CRepositoryTraceInserter::Insert( CTraceData* pTraceData )
    {
        m_rRepository.Insert(pTraceData);
        //CTraceDataRepository::Accessor		RepoAccess(m_rRepository);
        //
        //if ( RepoAccess )
        //{
        //    RepoAccess->Insert(pTraceData);
        //}
    }

}
