#ifndef _TRACEINSERTER_HPP_
#define _TRACEINSERTER_HPP_


namespace TraceClientCore
{
//	class CTraceDataRepository;
	class CTraceData;
	
	/**
	 *
	 */
	class CTraceInserter
	{
	public:		
		virtual void Insert( CTraceData* pTraceData ) = 0;
    };
}


#endif // _TRACEINSERTER_HPP_
