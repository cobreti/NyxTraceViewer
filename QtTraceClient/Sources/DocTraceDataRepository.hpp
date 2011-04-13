#ifndef UITRACEDATAREPOSITORY_HPP
#define UITRACEDATAREPOSITORY_HPP

#include <NyxOpaqueList.hpp>
#include "TraceDataRepository.hpp"
#include "DocTraceData.hpp"

/**
 *
 */
class IDocTraceDataRepository// : virtual public TraceClientCore::ITraceDataRepository
{
public:

    typedef     Nyx::OpaqueListIterator       IteratorHandle;

public:
    virtual void Insert(const TraceClientCore::CTraceData* pTraceData) = 0;
    virtual const CDocTraceData* Get( IteratorHandle hIterator ) = 0;
    virtual const CDocTraceData* Get( IteratorHandle hIterator ) const = 0;
    virtual size_t TracesCount() const = 0;

    virtual IteratorHandle AllocIterator() = 0;
    virtual IteratorHandle AllocIterator() const = 0;
    virtual void ReleaseIterator( IteratorHandle& hIterator ) const = 0;
    virtual void GetTailPos( IteratorHandle& hIterator ) = 0;
    virtual void GetTailPos( IteratorHandle& hIterator ) const = 0;
    virtual void GetHeadPos( IteratorHandle& hIterator ) = 0;
    virtual void GetHeadPos( IteratorHandle& hIterator ) const = 0;
    virtual void Clear() = 0;
    virtual void Copy( IteratorHandle hDst, IteratorHandle hSrc ) const = 0;
    virtual bool IsTail( IteratorHandle hIterator ) = 0;
    virtual bool IsTail( IteratorHandle hIterator ) const = 0;
    virtual bool AreEqual( IteratorHandle hPos1, IteratorHandle hPos2 ) const = 0;
    virtual bool IncrIterator( IteratorHandle hIterator ) = 0;
    virtual bool IncrIterator( IteratorHandle hIterator ) const = 0;
    virtual bool DecrIterator( IteratorHandle hIterator ) = 0;
    virtual bool DecrIterator( IteratorHandle hIterator ) const = 0;
};


/**
 *
 */
class CDocTraceDataRepository : virtual public Nyx::CMTInterfaceAccess<CDocTraceDataRepository, IDocTraceDataRepository>
{
public:
    CDocTraceDataRepository();
    virtual ~CDocTraceDataRepository();

protected:

    virtual void Insert(const TraceClientCore::CTraceData* pTraceData);
    virtual const CDocTraceData* Get( IteratorHandle hIterator );
    virtual const CDocTraceData* Get( IteratorHandle hIterator ) const;
    virtual size_t TracesCount() const;

    virtual IteratorHandle AllocIterator();
    virtual IteratorHandle AllocIterator() const;
    virtual void ReleaseIterator( IteratorHandle& hIterator ) const;
    virtual void GetTailPos( IteratorHandle& hIterator );
    virtual void GetTailPos( IteratorHandle& hIterator ) const;
    virtual void GetHeadPos( IteratorHandle& hIterator );
    virtual void GetHeadPos( IteratorHandle& hIterator ) const;
    virtual void Clear();
    virtual void Copy( IteratorHandle hDst, IteratorHandle hSrc ) const;
    virtual bool IsTail( IteratorHandle hIterator );
    virtual bool IsTail( IteratorHandle hIterator ) const;
    virtual bool AreEqual( IteratorHandle hPos1, IteratorHandle hPos2 ) const;
    virtual bool IncrIterator( IteratorHandle hIterator );
    virtual bool IncrIterator( IteratorHandle hIterator ) const;
    virtual bool DecrIterator( IteratorHandle hIterator );
    virtual bool DecrIterator( IteratorHandle hIterator ) const;

protected: // protected types

protected: // protected members

    Nyx::TOpaqueListRef<CDocTraceData*>       m_refTraces;
};

#endif // UITRACEDATAREPOSITORY_HPP
