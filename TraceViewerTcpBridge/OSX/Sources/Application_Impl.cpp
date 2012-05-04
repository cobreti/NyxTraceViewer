#include "Application.hpp"

#include <signal.h>
#include <unistd.h>


static void AbortHandler(int)
{
	CApplication::Instance().SignalTerminate();
}



/**
 *
 */
void CApplication::SetCancelHandlers()
{
	wprintf(L"[%i]\n", getpid());

	signal(SIGTERM, AbortHandler);
    signal(SIGABRT, AbortHandler);
    signal(SIGINT, AbortHandler);
}
