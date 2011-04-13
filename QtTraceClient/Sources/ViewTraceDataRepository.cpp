#include "ViewTraceDataRepository.hpp"

/****************************************
        CViewTraceDataRepository
****************************************/

/**
 *
 */
CViewTraceDataRepository::CViewTraceDataRepository()
{
}


/**
 *
 */
CViewTraceDataRepository::~CViewTraceDataRepository()
{
}


/**
 *
 */
const CViewTraceDataPos CViewTraceDataRepository::Begin() const
{
    return CViewTraceDataPos(m_Traces.begin(), 0);
}


/**
 *
 */
const CViewTraceDataPos CViewTraceDataRepository::End() const
{
    return CViewTraceDataPos(m_Traces.end(), -1);
}


/**
 *
 */
void CViewTraceDataRepository::Insert( CViewTraceData* pTrace )
{
    m_Traces.push_back(pTrace);

    m_MaxLineSize.setHeight( Nyx::Max(m_MaxLineSize.height(), pTrace->Size().height()) );

    m_LinesDisplaySize.rheight() += pTrace->Size().height();
    m_LinesDisplaySize.rwidth() = Nyx::Max( m_LinesDisplaySize.width(), pTrace->Size().width() );
}


/**
 *
 */
CViewTraceData* CViewTraceDataRepository::operator [] (const CViewTraceDataPos& pos) const
{
    return *pos.m_Pos;
}


/**
 *
 */
void CViewTraceDataRepository::MovePosTo( CViewTraceDataPos& pos, const double& rY )
{
    while ( pos.Y() + pos.Size().height() < rY )
        ++ pos;

    while ( pos.Y() > rY )
        -- pos;
}


/****************************************
        CViewTraceDataPos
****************************************/

/**
 *
 */
CViewTraceDataPos::CViewTraceDataPos() :
m_Y(0.0)
{
}


/**
 *
 */
CViewTraceDataPos::CViewTraceDataPos(const CViewTraceDataPos& rDataPos) :
m_Pos(rDataPos.m_Pos),
m_Y(rDataPos.m_Y)
{
}


/**
 *
 */
CViewTraceDataPos::~CViewTraceDataPos()
{
}


/**
 *
 */
const CViewTraceDataPos& CViewTraceDataPos::operator = (const CViewTraceDataPos& rDataPos)
{
    m_Pos = rDataPos.m_Pos;
    m_Y = rDataPos.m_Y;
    return *this;
}


/**
 *
 */
bool CViewTraceDataPos::operator != (const CViewTraceDataPos& rDataPos) const
{
    return m_Pos != rDataPos.m_Pos;
}


/**
 *
 */
void CViewTraceDataPos::operator ++ ()
{
    m_Y += (*m_Pos)->Size().height();
    ++ m_Pos;
}


/**
 *
 */
void CViewTraceDataPos::operator -- ()
{
    -- m_Pos;
    m_Y -= (*m_Pos)->Size().height();
}


/**
 *
 */
CViewTraceDataPos::CViewTraceDataPos(   const CViewTraceDataRepository::ViewTraceDataList::const_iterator& rPos,
                                        const double& rY ) :
    m_Pos(rPos),
    m_Y(rY)
{
}


/**
 *
 */
const QSizeF& CViewTraceDataPos::Size() const
{
    return (*m_Pos)->Size();
}
