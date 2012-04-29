#ifndef _TRACESVIEWSET_HPP_
#define _TRACESVIEWSET_HPP_

#include <set>

class CTracesView;


/**
 *
 */
class CTracesViewSet
{
    friend class CTracesViewSetIterator;

public:
    CTracesViewSet();
    explicit CTracesViewSet(const CTracesViewSet& set);
    ~CTracesViewSet();

    const CTracesViewSet& operator = (const CTracesViewSet& set);

    void Insert( CTracesView* pView );
    void Remove( CTracesView* pView );

protected:

    typedef     std::set<CTracesView*>      TViewSet;

protected:

    TViewSet            m_Views;
};


/**
 *
 */
class CTracesViewSetIterator
{
public:
    CTracesViewSetIterator(const CTracesViewSet& set);
    CTracesViewSetIterator(const CTracesViewSetIterator& iterator);
    ~CTracesViewSetIterator();

    const CTracesViewSetIterator& operator = (const CTracesViewSetIterator& iterator);

    bool Valid() const;

    bool MoveToFirst();
    bool MoveToNext();

    CTracesView* View() const;

protected:

    const CTracesViewSet&                         m_rSet;
    CTracesViewSet::TViewSet::const_iterator      m_Pos;
};


#endif // _TRACESVIEWSET_HPP_
