#include "ViewItem_TraceData.hpp"
#include "TracesPool.hpp"


/**
 *
 */
CViewItem_TraceData::CViewItem_TraceData(Nyx::CMemoryPool* pMemPool, const TraceClientCore::CTraceData* pTraceData ) :
ViewItemMemPoolObj(pMemPool),
m_pTraceData(pTraceData)
{
}


/**
 *
 */
CViewItem_TraceData::~CViewItem_TraceData()
{
}


/**
 *
 */
void CViewItem_TraceData::dbgOutputInfo()
{
    const TraceClientCore::CTraceData*     pTraceData = m_pTraceData;

    if ( pTraceData )
    {
        switch ( pTraceData->Type() )
        {
            case TraceClientCore::CTraceData::eTT_ConnectionStatus_Connection:
                Nyx::CTraceStream(0x0)
                    << Nyx::CTF_Text(L"CViewItem_TraceData - ")
                    << Nyx::CTF_Text(L"Module : '") << Nyx::CTF_Text(ModuleName().c_str()) << Nyx::CTF_Text(L"'")
                    << Nyx::CTF_Text(L" -- Connection");
                break;

            case TraceClientCore::CTraceData::eTT_ConnectionStatus_Disconnection:
                Nyx::CTraceStream(0x0)
                    << Nyx::CTF_Text(L"CViewItem_TraceData - ")
                    << Nyx::CTF_Text(L"Module : '") << Nyx::CTF_Text(ModuleName().c_str()) << Nyx::CTF_Text(L"'")
                    << Nyx::CTF_Text(L" -- Disconnection");
                break;

            case TraceClientCore::CTraceData::eTT_User:
                Nyx::CTraceStream(0x0)
                    << Nyx::CTF_Text(L"CViewItem_TraceData - ")
                    << Nyx::CTF_Text(L"Module : '") << Nyx::CTF_Text(ModuleName().c_str()) << Nyx::CTF_Text(L"'")
                    << Nyx::CTF_Text(L"TickCount : '") << Nyx::CTF_Text(pTraceData->TickCount().c_str()) << Nyx::CTF_Text(L"'")
                    << Nyx::CTF_Text(L" - ThreadId : '") << Nyx::CTF_Text(pTraceData->ThreadId().c_str()) << Nyx::CTF_Text(L"'")
                    << Nyx::CTF_Text(L" - Data : '") << Nyx::CTF_Text(pTraceData->Data().c_str()) << Nyx::CTF_Text(L"'");
                break;
        };

    }
    else
        Nyx::CTraceStream(0x0) << Nyx::CTF_Text(L"CViewItem_TraceData - ");
}


/**
 *
 */
const Nyx::CWString& CViewItem_TraceData::ModuleName() const
{
    return m_pTraceData->OwnerPool()->Name();
}


/**
 *
 */
const Nyx::CWString& CViewItem_TraceData::TickCount() const
{
    return m_pTraceData->TickCount();
}
