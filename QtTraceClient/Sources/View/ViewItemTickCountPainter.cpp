#include "ViewItemTickCountPainter.hpp"
#include "ViewItemSettings.hpp"
#include "ViewItem_TraceData.hpp"
#include "ViewSettings.hpp"
#include "ViewColumnsSettings.hpp"
#include "ViewColumnSettings.hpp"

#include "TimeStamp.hpp"

CViewItemPainterRef     CViewItemTickCountPainter::s_refPainter;


/**
 *
 */
CViewItemPainter* CViewItemTickCountPainter::Instance()
{
    if ( !s_refPainter.Valid() )
        s_refPainter = new CViewItemTickCountPainter();

    return s_refPainter;
}


/**
 *
 */
CViewItemTickCountPainter::CViewItemTickCountPainter() :
CViewItemTextPainter()
{
}


/**
 *
 */
CViewItemTickCountPainter::~CViewItemTickCountPainter()
{
}


/**
 *
 */
void CViewItemTickCountPainter::EvaluateSize(CViewSettings &settings, CViewItem &item)
{
    CViewItem_TraceData&        rItemData = static_cast<CViewItem_TraceData&>(item);
    QString                     text;

    GetTickCountString(rItemData, text);

    CViewItemTextPainter::EvaluateSize(settings, item, text);
}


/**
 *
 */
void CViewItemTickCountPainter::Display(const CViewSettings &settings, CDrawViewItemState &drawstate, CViewItem &item)
{
    CViewItem_TraceData&        rItemData = static_cast<CViewItem_TraceData&>(item);

    if ( item.GetOwner() == &item )
    {
        QString         text;

        GetTickCountString(rItemData, text);

        CViewItemTextPainter::Display(settings, drawstate, item, text);
    }
    else
    {
        const CViewColumnSettings&      rColSettings = settings.ColumnsSettings()[eVCI_TickCount];
        drawstate.TextPos().rx() += rColSettings.GetWidth();
    }
}


/**
 *
 */
void CViewItemTickCountPainter::GetTickCountString(CViewItem_TraceData& item, QString& text)
{
    text = QString().fromWCharArray(item.TraceData()->TickCount().c_str());

    //if ( (item.TraceData()->Flags() & NyxNet::TFlags_OSX) || (item.TraceData()->Flags() & NyxNet::TFlags_Linux) )
    //    GetUnixStyleTickCountString(item, text);
    //else if ( item.TraceData()->Flags() & NyxNet::TFlags_Windows )
    //    GetWindowsStyleTickCountString(item, text);
}


/**
 *
 */
void CViewItemTickCountPainter::GetUnixStyleTickCountString(CViewItem_TraceData &item, QString &text)
{
    Nyx::CWString       TimestampText;
    QString             time_text = QString().fromWCharArray(item.TraceData()->TickCount().c_str());
    long                sec = time_text.left(12).toLong();
    long                microsec = time_text.mid(12, 6).toLong();
    Nyx::UInt64         time_value;

    time_value = sec;
    time_value *= (1000 * 1000);
    time_value += microsec;

    TraceClientCore::CTimeStamp     TimeStamp( time_value, TraceClientCore::CTimeStamp::eIT_Microseconds );

    TimeStamp.ToString( TimestampText );
    text = QString().fromWCharArray(TimestampText.c_str());
}


/**
 *
 */
void CViewItemTickCountPainter::GetWindowsStyleTickCountString(CViewItem_TraceData &item, QString &text)
{
    Nyx::CWString       TimestampText;
    QString             time_text = QString().fromWCharArray(item.TraceData()->TickCount().c_str());
    long                sec = time_text.left(12).toLong();
    TraceClientCore::CTimeStamp     TimeStamp( sec, TraceClientCore::CTimeStamp::eIT_Milliseconds );

    TimeStamp.ToString( TimestampText );
    text = QString().fromWCharArray(TimestampText.c_str());
}


