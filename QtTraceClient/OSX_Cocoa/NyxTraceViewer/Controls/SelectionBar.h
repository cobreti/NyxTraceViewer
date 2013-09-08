//
//  SelectionBar.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-07.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#include "ActionHandlerInfo.h"
#include <vector>


@class CToggleFlatBtn;

typedef std::vector<CToggleFlatBtn*>      TBtnsVector;

@interface CSelectionBar : NSControl
{
    TBtnsVector             m_Btns;
    CActionHandlerInfo      m_BtnSelectionChangedHandler;
}

- (void)addBtn: (CToggleFlatBtn*)btn;
- (CToggleFlatBtn*)activeBtn;
- (void)calcSize;
- (BOOL)isFlipped;
- (NSSize) intrinsicContentSize;
- (void)onBtnClicked: (id)sender;
- (void)dealloc;
- (void)setBtnSelectionChangedHandler: (const CActionHandlerInfo&)handler;

@end
