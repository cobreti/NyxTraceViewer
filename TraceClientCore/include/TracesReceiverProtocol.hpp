#ifndef _TRACESRECEIVERPROTOCOL_HPP_
#define _TRACESRECEIVERPROTOCOL_HPP_

#include <Nyx.hpp>

namespace Nyx
{
	class IStreamRW;
}

namespace TraceClientCore
{
	/**
	 *
	 */
	class CTracesReceiverProtocol
	{
	public:
		CTracesReceiverProtocol();
		virtual ~CTracesReceiverProtocol();

		virtual Nyx::NyxResult HandleStream( Nyx::IStreamRW& rStream ) = 0;
	};
}



#endif // _TRACESRECEIVERPROTOCOL_HPP_
