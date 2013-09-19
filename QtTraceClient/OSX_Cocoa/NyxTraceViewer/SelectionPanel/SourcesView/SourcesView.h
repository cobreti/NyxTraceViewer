//
//  CTracesGroupView.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-25.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class CRepositoriesListCtrl;

class CTracesGroupInfo;

@interface CSourcesView : NSScrollView
{   
    CRepositoriesListCtrl*      mCtrl;
}

- (BOOL)isFlipped;
- (void)awakeFromNib;
- (void)dealloc;
- (void)onNewChannel: (NSDictionary*)params;
- (void)refreshForGroup: (CTracesGroupInfo*)pGroupInfo;

@end
