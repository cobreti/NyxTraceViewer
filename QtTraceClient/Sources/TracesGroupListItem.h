#ifndef TRACESGROUPLISTITEM_H
#define TRACESGROUPLISTITEM_H

#include "TraceClientCoreModule.hpp"

#include <QListWidgetItem>


class CTracesGroupListItem : public QListWidgetItem
{
public:

    CTracesGroupListItem(TraceClientCore::CTracesGroup* pGroup, QListWidget* pParent);
    virtual ~CTracesGroupListItem();


    TraceClientCore::CTracesGroup* Group() const { return m_pGroup; }


protected:

    TraceClientCore::CTracesGroup*      m_pGroup;
};


#endif // TRACESGROUPLISTITEM_H
