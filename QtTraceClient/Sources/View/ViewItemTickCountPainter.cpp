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
//    QString                     time_text = QString().fromWCharArray(rItemData.TraceData()->TickCount().c_str());
//    QString                     text = time_text + " / " + time_text;
    QString                     text;

    GetTickCountString(rItemData, text);

    CViewItemTextPainter::EvaluateSize(settings, item, text);
}


/**
 *
 */
void CViewItemTickCountPainter::Display(const CViewSettings &settings, CDrawViewItemState &drawstate, CViewItem &item)
{
//    const long      kSecPerMin = 60;
//    const long      kSecPerHours = kSecPerMin * 60;
//    const long      kSecPerDays = kSecPerHours * 24;
//    const long      kSecPerYear = kSecPerDays * 365;

    CViewItem_TraceData&        rItemData = static_cast<CViewItem_TraceData&>(item);

    if ( item.GetOwner() == &item )
    {
        QString         text;
//        QString                     time_text = QString().fromWCharArray(rItemData.TraceData()->TickCount().c_str());
//        QString                     sec_text = time_text.left(12);
//        long                        sec = sec_text.toLong();
//        long                        hours, minutes, micro, days, year;

//        micro = time_text.mid(12, 6).toLong();

//        year = sec / kSecPerYear;
//        sec -= year * kSecPerYear;

//        days = sec / kSecPerDays;
//        sec -= days * kSecPerDays;

//        hours = sec / kSecPerHours;
//        sec -= hours * kSecPerHours;

//        minutes = sec / kSecPerMin;
//        sec -= minutes * kSecPerMin;

//        QString                     formated_time = QString::number(year) + ":" +
//                                                    QString::number(days) + ":" +
//                                                    QString::number(hours) + ":" +
//                                                    QString::number(minutes) + ":" +
//                                                    QString::number(sec) + ":" +
//                                                    QString::number(micro);

//        QString                     text = formated_time + " / " + time_text;

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
    if ( (item.TraceData()->Flags() & NyxNet::TFlags_OSX) || (item.TraceData()->Flags() & NyxNet::TFlags_Linux) )
        GetUnixStyleTickCountString(item, text);
    else if ( item.TraceData()->Flags() & NyxNet::TFlags_Windows )
        GetWindowsStyleTickCountString(item, text);
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
    text += " " + time_text;
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


