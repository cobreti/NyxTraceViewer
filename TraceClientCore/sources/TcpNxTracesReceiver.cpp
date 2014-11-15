#include "TcpNxTracesReceiver.hpp"
#include "TraceChannel.hpp"
#include "TraceClientCoreModule.hpp"
#include "TraceNxStreamReader.hpp"
#include "TcpTracesReceiversSvr.hpp"
#include "TcpTracesReceiversTable.hpp"
#include <NyxSwap.hpp>

namespace TraceClientCore
{
    /**
     *
     */
    CTcpNxTracesReceiver::CTcpNxTracesReceiver(CTcpNxTracesReceiversSvr* pSvr, NyxNet::IConnection* pConnection) :
    m_pConnection(pConnection),
    m_pServer(pSvr),
    m_pChannel(NULL)
    {
        GetClientAddress(pConnection);

        TraceClientCore::CModule::Instance().ConnectionsMgr().onNewConnection(m_ClientAddress);
//        CTcpNxTracesReceiversTable::MethodsRef    refMethods = m_pServer->ReceiversTable().GetMethods();
//
//        refMethods->Insert(this);
    }
    
    
    /**
     *
     */
    CTcpNxTracesReceiver::~CTcpNxTracesReceiver()
    {
//        CTcpNxTracesReceiversTable::MethodsRef    refMethods = m_pServer->ReceiversTable().GetMethods();
//
//        refMethods->Remove(this);
    }
    
    
    /**
     *
     */
    void CTcpNxTracesReceiver::HandleStream( NyxNet::INxStreamRW& rStream )
    {
        NyxNet::CNxStreamReader     Reader(rStream);
        
        if ( !Reader.Valid() )
            return;
        
        switch (Reader.DataType())
        {
            case NyxNet::eNxDT_TxtTraceData:
                HandleTxtTraceStream(Reader);
                break;
                
            default:
                HandleTraceStream(Reader);
        }
    }
    
    
    /**
     *
     */
    Nyx::NyxResult CTcpNxTracesReceiver::OnNewConnection( NyxNet::IConnection* pConnection, NyxNet::INxConnectionHandler*& pCloneHandler )
    {
        
        return Nyx::kNyxRes_Success;
    }
    
    
    /**
     *
     */
    void CTcpNxTracesReceiver::OnConnectionTerminated( NyxNet::IConnection* pConnection )
    {
        TraceClientCore::CModule::Instance().ConnectionsMgr().onCloseConnection(m_ClientAddress, m_ChannelsSet);

        delete this;
    }
    
    
    /**
     *
     */
    void CTcpNxTracesReceiver::HandleTraceStream(NyxNet::CNxStreamReader& rStreamReader )
    {
        NyxNet::NxDataSize          TotalSize = 0;
        Nyx::UInt32                 SectionsCount = 0;
        QString                     Name;
        
        try
        {
            // read sections count
            {
                NyxNet::CNxSectionStreamReader        SectionReader(rStreamReader);
                
                m_Buffer.Resize(SectionReader.Size());
                SectionReader.Read(m_Buffer, SectionReader.Size());
                
                SectionsCount = *m_Buffer.GetBufferAs<Nyx::UInt32>();
            }
            
            // read module name
            {
                NyxNet::CNxSectionStreamReader      SectionReader(rStreamReader);
                
                m_Buffer.Resize(SectionReader.Size());
                SectionReader.Read(m_Buffer, SectionReader.Size());
                
                Name = m_Buffer.GetBufferAs<const char>();
            }
            
            CModule&            rModule = CModule::Instance();
            CTraceChannel*      pChannel = rModule.TraceChannels().Get(Name, true);
            
            -- SectionsCount;
            
            if ( pChannel )
            {
                m_ChannelsSet.insert(pChannel);
                m_pChannel = pChannel;
                
                CTraceNxStreamReader        TraceReader( pChannel->Pool() );

                TraceReader.Read(SectionsCount, rStreamReader, *pChannel);
//                CTraceData*                 pTrace = NULL;
                
//                pTrace = TraceReader.Read(SectionsCount, rStreamReader);
//                if ( pTrace )
//                    pChannel->Insert(pTrace);
            }
            else
            {
                while ( SectionsCount -- > 0 )
                {
                    NyxNet::CNxSectionStreamReader        SectionReader(rStreamReader);
                    
                    m_Buffer.Resize(SectionReader.Size());
                    SectionReader.Read(m_Buffer, SectionReader.Size());
                    TotalSize += SectionReader.Size();
                }
            }
        }
        catch (...)
        {
            Nyx::CTraceStream(0x0).Write("Error reading from pipe");
        }        
    }

    
    /**
     *
     */
    void CTcpNxTracesReceiver::HandleTxtTraceStream( NyxNet::CNxStreamReader& rStreamReader )
    {
        NyxNet::NxDataSize          TotalSize = 0;
        Nyx::UInt32                 SectionsCount = 0;
        Nyx::CAString               Name;
        
        //            CModule&                    rModule = CModule::Instance();
        //            CTraceChannel*              pChannel = rModule.TraceChannels().Get(Name);
        CTraceNxStreamReader        TraceReader( NULL /*pChannel->Pool()*/ );
        //            CTraceData*                 pTraceData = NULL;
        
        // read sections count
        {
            NyxNet::CNxSectionStreamReader        SectionReader(rStreamReader);
            
            m_Buffer.Resize(SectionReader.Size());
            SectionReader.Read(m_Buffer, SectionReader.Size());
            
            SectionsCount = *m_Buffer.GetBufferAs<Nyx::UInt32>();
            
            if ( SectionReader.RequiresBytesSwap() )
                SectionsCount = Nyx::Swap_UInt32(SectionsCount);
        }
        
        // read module name
        {
            NyxNet::CNxSectionStreamReader      SectionReader(rStreamReader);
            
            m_Buffer.Resize(SectionReader.Size());
            SectionReader.Read(m_Buffer, SectionReader.Size());
            
            Name = m_Buffer.GetBufferAs<const char>();
            
            NYXTRACE(0x0, L"module name : " << Nyx::CTF_AnsiText(Name.c_str()) );
        }
        
        // read thread id
        {
            NyxNet::CNxSectionStreamReader      SectionReader(rStreamReader);
            
            m_Buffer.Resize(SectionReader.Size());
            SectionReader.Read(m_Buffer, SectionReader.Size());
            
            const char* pThreadId = m_Buffer.GetBufferAs<const char>();
            
            NYXTRACE(0x0, L"thread id : " << Nyx::CTF_AnsiText(pThreadId) );
        }
        
        // read tickcount
        {
            NyxNet::CNxSectionStreamReader      SectionReader(rStreamReader);
            
            m_Buffer.Resize(SectionReader.Size());
            SectionReader.Read(m_Buffer, SectionReader.Size());
            
            const char* pTickCount = m_Buffer.GetBufferAs<const char>();
            
            NYXTRACE(0x0, L"tick count : " << Nyx::CTF_AnsiText(pTickCount) );
        }
        
        // read text
        {
            NyxNet::CNxSectionStreamReader      SectionReader(rStreamReader);
            
            m_Buffer.Resize(SectionReader.Size());
            SectionReader.Read(m_Buffer, SectionReader.Size());
            
            const char* pText = m_Buffer.GetBufferAs<const char>();
            
            NYXTRACE(0x0, L"trace text : " << Nyx::CTF_AnsiText(pText) );
        }
    }

    void CTcpNxTracesReceiver::GetClientAddress(NyxNet::IConnection *pConnection)
    {
        NyxNet::CSocketRef refSocket = pConnection->Socket();
        if ( !refSocket.Valid() )
            return;

        NyxNet::CTcpIpSocketRef refTcpIpSocket = refSocket->TcpIpSocket();
        if ( !refTcpIpSocket.Valid() )
            return;

        m_ClientAddress = refTcpIpSocket->ClientAddress();

    }

}


