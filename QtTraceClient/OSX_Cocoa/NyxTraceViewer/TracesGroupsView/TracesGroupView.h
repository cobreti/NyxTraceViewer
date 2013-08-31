//
//  CTracesGroupView.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-25.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class CRepositoriesListCtrl;

@interface CTracesGroupView : NSScrollView
{
//    NSSplitView*        m_SplitView;
//    NSView*             m_GroupsView;
//    NSView*             m_RepositoriesView;
    
    CRepositoriesListCtrl*      mCtrl;
}

- (BOOL)isFlipped;
- (void)awakeFromNib;
- (void)dealloc;

@end
