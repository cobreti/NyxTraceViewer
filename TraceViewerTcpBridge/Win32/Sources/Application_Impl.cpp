#include "Application.hpp"


static void AbortHandler(int)
{
	CApplication::Instance().SignalTerminate();
}



/**
 *
 */
void CApplication::SetCancelHandlers()
{
}
