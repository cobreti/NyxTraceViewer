//
//  SelectionPanelBar.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-07.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#include <map>

@class CToggleFlatBtn;

typedef std::map<int, NSCell*>      TCellsMap;
typedef std::map<int, CToggleFlatBtn*>      TToggleFlatBtnsMap;

@interface CSelectionPanelBar : NSControl
{
    TToggleFlatBtnsMap      m_Btns;
    TCellsMap               m_Cells;
}

- (void)calcSize;
- (void)dealloc;
- (BOOL)isFlipped;
- (void)viewDidEndLiveResize;
- (void)onSourcesSelected: (id)sender;

@end
