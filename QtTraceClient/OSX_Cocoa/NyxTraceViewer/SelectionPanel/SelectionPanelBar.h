//
//  SelectionPanelBar.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-07.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "../Controls/SelectionBar.h"

#include "../Controls/ActionHandlerInfo.h"
#include <map>

@class CToggleFlatBtn;


enum {
    kSelectionPanelBar_SourcesPanel = 1,
    kSelectionPanelBar_ChannelsPanel = 2
};


@interface CSelectionPanelBar : NSControl
{
    CSelectionBar*          m_SelectionBar;
    CActionHandlerInfo      m_PanelSelectionChangedHandler;
}

- (IBAction) onSelectionBarSelectedBtnChanged: (id)sender;

- (void)calcSize;
- (void)dealloc;
- (BOOL)isFlipped;
- (void)viewDidEndLiveResize;
- (void)onSourcesSelected: (id)sender;
- (void)setPanelSelectionChangedHandler: (const CActionHandlerInfo&)handler;
- (int)selectedPanel;


@end
