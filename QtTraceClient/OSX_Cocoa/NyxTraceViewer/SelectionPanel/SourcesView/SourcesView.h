//
//  CTracesGroupView.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-25.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class CRepositoriesListCtrl;

@interface CSourcesView : NSScrollView
{   
    CRepositoriesListCtrl*      mCtrl;
}

- (BOOL)isFlipped;
- (void)awakeFromNib;
- (void)dealloc;
- (void)onNewChannel: (NSDictionary*)params;

@end
