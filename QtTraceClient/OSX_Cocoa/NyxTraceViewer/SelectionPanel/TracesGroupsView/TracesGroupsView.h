//
//  TracesGroupsView.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-08.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class CTracesGroupsListCtrl;

@interface CTracesGroupsView : NSScrollView
{
    CTracesGroupsListCtrl*
    m_GroupsListCtrl;
}

@end
