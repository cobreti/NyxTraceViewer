//
//  TracesWindowController.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-08-25.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface CTracesWindowController : NSWindowController <NSToolbarDelegate>
{
    CGFloat     m_LastChannelsPanelWidth;
}

@property (assign) IBOutlet NSSplitView *m_SplitView;

- (IBAction)onChannelsShowHide:(id)sender;
- (BOOL)validateToolbarItem:(NSToolbarItem *)theItem;
- (NSArray*)toolbarAllowedItemIdentifiers:(NSToolbar*)toolbar;
@end
