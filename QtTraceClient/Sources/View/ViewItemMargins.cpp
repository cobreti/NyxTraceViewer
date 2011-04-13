#include "ViewItemMargins.hpp"


/**
 *
 */
CViewItemMargins::CViewItemMargins() :
m_Top(0.0), m_Left(0.0), m_Bottom(0.0), m_Right(0.0)
{
}


/**
 *
 */
CViewItemMargins::CViewItemMargins(const CViewItemMargins& margins) :
m_Top(margins.m_Top), m_Left(margins.m_Left),
m_Bottom(margins.m_Bottom), m_Right(margins.m_Right)
{
}


/**
 *
 */
CViewItemMargins::CViewItemMargins(const qreal &left, const qreal &top, const qreal &right, const qreal &bottom) :
m_Top(top), m_Left(left), m_Bottom(bottom), m_Right(right)
{
}


/**
 *
 */
CViewItemMargins::~CViewItemMargins()
{
}


/**
 *
 */
const CViewItemMargins& CViewItemMargins::operator = (const CViewItemMargins& margins)
{
    m_Left = margins.m_Left;
    m_Right = margins.m_Right;
    m_Top = margins.m_Top;
    m_Bottom = margins.m_Bottom;

    return *this;
}
