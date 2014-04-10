#include "ViewSearchEngine.h"
#include "TracesView.h"
//#include "View/Walkers/ViewItemsWalker.hpp"
//#include "View/ViewItem_TraceData.hpp"



/**
 *
 */
CViewSearchEngine::CViewSearchEngine( CTracesView& rView  ) :
    m_rView(rView)
{
    m_refSearchedLineHighlighter = new CViewItemHighlighter_SearchedLine(this);

    m_rView.Highlighters()->Add( m_refSearchedLineHighlighter );
}


/**
 *
 */
CViewSearchEngine::~CViewSearchEngine()
{
}


/**
 *
 */
void CViewSearchEngine::Next()
{
//    CViewItem_TraceData*                        pFoundItem = NULL;

//    {
//        CViewItemsWalker::MethodsInterfaceRef       refWalkerMethods(m_rView.ItemsWalker());
//        size_t                                      StartLineNo = refWalkerMethods->LineNo();
//        size_t                                      LineNo = 0;
//        bool                                        bEndReached = false;
//        CViewItem*                                  pStartItem = refWalkerMethods->Item();

//        refWalkerMethods->PushState();

//        // move pass last found occurence
//        if ( m_FoundPos )
//        {
//            while ( refWalkerMethods->ValidPos() && refWalkerMethods->ItemNumber() <= m_FoundPos.ItemNumber()  )
//            {
//                if ( !refWalkerMethods->MoveToNext() )
//                {
////                    refWalkerMethods->MoveToBegin();
//                    break;
//                }
//            }

//            while ( refWalkerMethods->ValidPos() && refWalkerMethods->ItemNumber() > m_FoundPos.ItemNumber()+1  )
//                !refWalkerMethods->MoveToPrevious();
//        }


//        // find next occurence
//        while ( refWalkerMethods->ValidPos() && pFoundItem == NULL )
//        {
//            if ( refWalkerMethods->Item()->IsOfKind( CViewItem::eViewItem_TraceData ) )
//            {
//                pFoundItem = static_cast<CViewItem_TraceData*>( refWalkerMethods->Item() );

//                QString     text = QString::fromStdWString( pFoundItem->TraceData()->Data().c_str() );
//                if ( m_refHighlighter->Pattern()->Match(text, 0).Length() > 0 )
//                {
//                    m_FoundPos = refWalkerMethods->ItemNumber();
//                    LineNo = refWalkerMethods->LineNo();
//                }
//                else
//                {
//                    pFoundItem = NULL;
//                }
//            }

//            if ( !refWalkerMethods->MoveToNext() )
//            {
//                break;
////                refWalkerMethods->MoveToBegin();
//            }

//            if ( pStartItem == refWalkerMethods->Item() )
//                break;
//        }

//        refWalkerMethods->PopState();


//        // make sure item is visible
//        if ( pFoundItem )
//        {
//            int VisibleLinesCount = m_rView.NumberOfLinesVisibles();

//            if ( (LineNo < StartLineNo) || (LineNo > StartLineNo + VisibleLinesCount - 1) )
//            {
//                int HalfVisibleCount = VisibleLinesCount / 2;

//                if ( LineNo > HalfVisibleCount )
//                    LineNo -= HalfVisibleCount;
//                else
//                    LineNo = 0;

//                refWalkerMethods->MoveToLine(LineNo);
//            }
//        }
//        else
//        {
//            m_FoundPos = XFindPos();
//        }
//    }

//    if ( pFoundItem != NULL )
//        m_rView.Invalidate(true);
}


/**
 *
 */
void CViewSearchEngine::Previous()
{
//    CViewItem_TraceData*                        pFoundItem = NULL;

//    {
//        CViewItemsWalker::MethodsInterfaceRef       refWalkerMethods(m_rView.ItemsWalker());
//        size_t                                      StartLineNo = refWalkerMethods->LineNo();
//        size_t                                      LineNo = 0;
//        bool                                        bEndReached = false;
//        CViewItem*                                  pStartItem = refWalkerMethods->Item();

//        refWalkerMethods->PushState();

//        // move pass last found occurence
//        if ( m_FoundPos )
//        {
//            while ( refWalkerMethods->ValidPos() && refWalkerMethods->ItemNumber() < m_FoundPos.ItemNumber()-1  )
//                refWalkerMethods->MoveToNext();

//            while ( refWalkerMethods->ValidPos() && refWalkerMethods->ItemNumber() >= m_FoundPos.ItemNumber()  )
//                refWalkerMethods->MoveToPrevious();
//        }


//        // find next occurence
//        while ( refWalkerMethods->ValidPos() && pFoundItem == NULL )
//        {
//            if ( refWalkerMethods->Item()->IsOfKind( CViewItem::eViewItem_TraceData ) )
//            {
//                pFoundItem = static_cast<CViewItem_TraceData*>( refWalkerMethods->Item() );

//                QString     text = QString::fromStdWString( pFoundItem->TraceData()->Data().c_str() );
//                if ( m_refHighlighter->Pattern()->Match(text, 0).Length() > 0 )
//                {
//                    m_FoundPos = refWalkerMethods->ItemNumber();
//                    LineNo = refWalkerMethods->LineNo();
//                }
//                else
//                {
//                    pFoundItem = NULL;
//                }
//            }

//            if ( !refWalkerMethods->MoveToPrevious() )
//                break;
//        }

//        refWalkerMethods->PopState();


//        // make sure item is visible
//        if ( pFoundItem )
//        {
//            int VisibleLinesCount = m_rView.NumberOfLinesVisibles();

//            if ( (LineNo < StartLineNo) || (LineNo > StartLineNo + VisibleLinesCount - 1) )
//            {
//                int HalfVisibleCount = VisibleLinesCount / 2;

//                if ( LineNo > HalfVisibleCount )
//                    LineNo -= HalfVisibleCount;
//                else
//                    LineNo = 0;

//                refWalkerMethods->MoveToLine(LineNo);
//            }
//        }
//    }

//    if ( pFoundItem != NULL )
//        m_rView.Invalidate(true);
}


/**
 *
 */
void CViewSearchEngine::Clear()
{
    m_FoundPos = XFindPos();
//    m_rView.Invalidate(true);
}

