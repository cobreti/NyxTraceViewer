//
//  CTracesGroupView.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-25.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface CTracesGroupView : NSView
{
    NSSplitView*        m_SplitView;
    NSView*             m_GroupsView;
    NSView*             m_RepositoriesView;
}

- (BOOL)isFlipped;
- (void)awakeFromNib;

@end
