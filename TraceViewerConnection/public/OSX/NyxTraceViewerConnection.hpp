#ifndef _NYXTRACEVIEWERCONNECTION_HPP_
#define _NYXTRACEVIEWERCONNECTION_HPP_


namespace Nyx
{
    /**
     *
     */
    class CTraceViewerConnection
    {
    public:

        enum ECharType
        {
            eCT_Ansi = 0,
            eCT_WideChar
        };

        //static void CreateInstance(const char* szTraceLinkName, ECharType charType);
        static void ReleaseInstance();
        static CTraceViewerConnection& Instance();

    public:

        virtual void Write( const char* szData, ... ) = 0;
        virtual void Write( const wchar_t* wszData, ... ) = 0;
    };
    
    
    /**
     *
     */
    class CTraceViewerConnection_Pipe_Ansi : public CTraceViewerConnection
    {
    public:
        static void CreateInstance(const char* ModuleName);
    };
    
    
    /**
     *
     */
    class CTraceViewerConnection_Pipe_WChar : public CTraceViewerConnection
    {
    public:
        static void CreateInstance(const char* ModuleName);
    };


    /**
     *
     */
    class CTraceViewerConnection_TcpIp_Ansi : public CTraceViewerConnection
    {
    public:
        static void CreateInstance(const char* ModuleName, const char* addr);
    };


    /**
     *
     */
    class CTraceViewerConnection_TcpIp_WChar : public CTraceViewerConnection
    {
    public:
        static void CreateInstance(const char* ModuleName, const char* addr);
    };
};


#endif // _NYXTRACEVIEWERCONNECTION_HPP_

