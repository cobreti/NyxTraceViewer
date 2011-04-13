#ifndef VIEWTRACEDATAREPOSITORY_HPP
#define VIEWTRACEDATAREPOSITORY_HPP

#include "ViewTraceData.hpp"

#include <list>

class CViewTraceDataPos;


/**
 *
 */
class CViewTraceDataRepository
{
    friend class CViewTraceDataPos;

public:
    CViewTraceDataRepository();
    virtual ~CViewTraceDataRepository();

    virtual const CViewTraceDataPos Begin() const;
    virtual const CViewTraceDataPos End() const;

    virtual void Insert( CViewTraceData* pTrace );

    CViewTraceData* operator [] (const CViewTraceDataPos& pos) const;

    size_t Size() const { return m_Traces.size(); }

    const QSizeF& LinesDisplaySize() const      { return m_LinesDisplaySize; }
	const QSizeF& MaxLineSize() const			{ return m_MaxLineSize; }

    virtual void MovePosTo( CViewTraceDataPos& pos, const double& rY );

protected:

    typedef     std::list<CViewTraceData*>       ViewTraceDataList;

protected:

    ViewTraceDataList       m_Traces;
    QSizeF                  m_LinesDisplaySize;
	QSizeF					m_MaxLineSize;
};


/**
 *
 */
class CViewTraceDataPos
{
    friend class CViewTraceDataRepository;

public:
    CViewTraceDataPos();
    CViewTraceDataPos(const CViewTraceDataPos& rDataPos);
    virtual ~CViewTraceDataPos();

    const CViewTraceDataPos& operator = (const CViewTraceDataPos& rDataPos);

    bool operator != (const CViewTraceDataPos& rDataPos) const;

    void operator ++ ();
    void operator -- ();

    double Y() const        { return m_Y; }

    const QSizeF& Size() const;

    bool Valid() const { return m_Y != -1; }

protected:

    CViewTraceDataPos(  const CViewTraceDataRepository::ViewTraceDataList::const_iterator& rPos,
                        const double& rY );

protected:

    CViewTraceDataRepository::ViewTraceDataList::const_iterator     m_Pos;
    double                                                          m_Y;
};

#endif // VIEWTRACEDATAREPOSITORY_HPP
