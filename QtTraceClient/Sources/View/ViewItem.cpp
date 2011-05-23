#include "ViewItem.hpp"
#include "ViewSettings.hpp"
#include "ViewColumnsSettings.hpp"
#include "ViewColumnSettings.hpp"


/**
 *
 */
CViewItem::CViewItem() :
m_LineNumber(0)
{
}


/**
 *
 */
CViewItem::~CViewItem()
{
}


/**
 *
 */
void CViewItem::dbgOutputInfo()
{
    Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"CViewItem");
}


/**
 *
 */
void CViewItem::AddSize(const QSizeF &size)
{
    m_Size.rheight() = Nyx::Max(size.height(), m_Size.height());
    m_Size.rwidth() += size.width();
}


/**
 *
 */
void CViewItem::EvaluateSize(CViewSettings& settings)
{
    CViewColumnsOrder&  rColsOrder = settings.ColumnsSettings().Order();
    size_t              ColsCount = rColsOrder.Count();
    size_t              index = 0;

    m_Size = QSizeF(0.0, 0.0);

    for ( index = 0; index < ColsCount; ++index )
    {
        CViewColumnSettings&        rColSettings = settings.ColumnsSettings()[rColsOrder[index]];

        if ( rColSettings.GetVisible() )
        {
            CViewItemPainter*           pPainter = m_Painters[ rColSettings.GetPainterId() ];

            if ( pPainter )
                pPainter->EvaluateSize(settings, *this);
        }
    }

    m_Flags.set(eVIF_SizeCalculated);
}


/**
 *
 */
void CViewItem::Display(const CViewSettings& settings, CDrawViewItemState &drawstate)
{
    if ( !m_Flags.test(eVIF_SizeCalculated))
        return;

    const CViewColumnsOrder&    rColsOrder = settings.ColumnsSettings().Order();
    size_t                      ColsCount = rColsOrder.Count();
    size_t                      index = 0;
    CViewItemPainter*           pPainter = NULL;

    pPainter = m_Painters[ CViewItemPainter::ePId_Row ];
    if ( pPainter )
        pPainter->Display(settings, drawstate, *this);

    for ( index = 0; index < ColsCount; ++index )
    {
        const CViewColumnSettings&        rColSettings = settings.ColumnsSettings()[rColsOrder[index]];

        if ( rColSettings.GetVisible() )
        {
            pPainter = m_Painters[ rColSettings.GetPainterId() ];

            if ( pPainter )
                pPainter->Display(settings, drawstate, *this);
        }
    }

    drawstate.TextPos().ry() += m_Size.height();
}


/**
 *
 */
void CViewItem::SetFlag( CViewItem::EViewItemFlags flag, bool status )
{
    m_Flags.set(flag, status);
}


/**
 *
 */
void CViewItem::RemoveFlag( CViewItem::EViewItemFlags flag )
{
    m_Flags.reset(flag);
}


/**
 *
 */
bool CViewItem::HasFlag(EViewItemFlags flag) const
{
    return m_Flags[flag];
}
