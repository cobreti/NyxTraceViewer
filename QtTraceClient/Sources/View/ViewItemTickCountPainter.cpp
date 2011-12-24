#include "ViewItemTickCountPainter.hpp"
#include "ViewItemSettings.hpp"
#include "ViewItem_TraceData.hpp"
#include "ViewSettings.hpp"
#include "ViewColumnsSettings.hpp"
#include "ViewColumnSettings.hpp"


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
}


/**
 *
 */
void CViewItemTickCountPainter::GetUnixStyleTickCountString(CViewItem_TraceData &item, QString &text)
{
    const long      kSecPerMin = 60;
    const long      kSecPerHours = kSecPerMin * 60;
    const long      kSecPerDays = kSecPerHours * 24;
    const long      kSecPerYear = kSecPerDays * 365;

    QString         time_text = QString().fromWCharArray(item.TraceData()->TickCount().c_str());
    long            sec = time_text.left(12).toLong();
    long            hours, minutes, micro, days, year;
    QString         strYear, strDays, strHours, strMinutes, strSec;

    micro = time_text.mid(12, 6).toLong();

    year = sec / kSecPerYear;
    sec -= year * kSecPerYear;

    days = sec / kSecPerDays;
    sec -= days * kSecPerDays;

    hours = sec / kSecPerHours;
    sec -= hours * kSecPerHours;

    minutes = sec / kSecPerMin;
    sec -= minutes * kSecPerMin;

    strYear = QString::number(year);
    while ( strYear.length() < 3 )
        strYear = strYear.prepend("0");

    strDays = QString::number(days);
    while ( strDays.length() < 2 )
        strDays = strDays.prepend("0");

    strHours = QString::number(hours);
    while ( strHours.length() < 2 )
        strHours = strHours.prepend("0");

    strMinutes = QString::number(minutes);
    while ( strMinutes.length() < 2 )
        strMinutes = strMinutes.prepend("0");

    strSec = QString::number(sec);
    while ( strSec.length() < 2 )
        strSec = strSec.prepend("0");

    text =      strYear + ":" +
                strDays + ":" +
                strHours + ":" +
                strMinutes + ":" +
                strSec + ":" +
                time_text.mid(12, 6);

}


/**
 *
 */
void CViewItemTickCountPainter::GetWindowsStyleTickCountString(CViewItem_TraceData &item, QString &text)
{

}


