#ifndef VIEWITEMINSERTER_HPP
#define VIEWITEMINSERTER_HPP


namespace TraceClientCore
{
    class CTraceData;
}


/**
 *
 */
class CViewItemInserter
{
public:
    CViewItemInserter();
    virtual ~CViewItemInserter();

    virtual void InsertViewItem( const TraceClientCore::CTraceData* pTraceData ) = 0;
};


#endif // VIEWITEMINSERTER_HPP
