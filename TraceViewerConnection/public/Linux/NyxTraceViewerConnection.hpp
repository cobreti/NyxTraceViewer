#ifndef _TRACECLIENTLINK_HPP_
#define _TRACECLIENTLINK_HPP_


class CTraceClientLink
{
public:

    enum ECharType
    {
        eCT_Ansi = 0,
        eCT_WideChar
    };

	static void CreateInstance(const char* szTraceLinkName, ECharType charType);
	static void ReleaseInstance();
    static void CreateDllInstance(void* pModule, const char* szTraceLinkName, ECharType charType);
    static void ReleaseDllInstance(void* pModule);
	static CTraceClientLink& Instance();

public:

	virtual void Write( const char* szData, ... ) = 0;
    virtual void Write( const wchar_t* wszData, ... ) = 0;
};


#endif // _TRACECLIENTLINK_HPP_
