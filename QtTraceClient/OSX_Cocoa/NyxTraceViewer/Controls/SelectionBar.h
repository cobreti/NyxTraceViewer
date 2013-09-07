//
//  SelectionBar.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-07.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#include <vector>


@class CToggleFlatBtn;

typedef std::vector<CToggleFlatBtn*>      TBtnsVector;

@interface CSelectionBar : NSControl
{
    TBtnsVector            m_Btns;
}

- (void)addBtn: (CToggleFlatBtn*)btn;
- (void)calcSize;
- (BOOL)isFlipped;
- (NSSize) intrinsicContentSize;
- (void)onBtnClicked: (id)sender;
- (void)dealloc;

@end
