//
//  ToggleFlatBtn.h
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-07.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import <Cocoa/Cocoa.h>

enum {
    kToggleFlatBtn_OffState = 0,
    kToggleFlatBtn_OnState = 1,
    kToggleFlatBtn_StatesCount = 2
};

@interface CToggleFlatBtn : NSControl
{
    NSCell*         m_Cells[kToggleFlatBtn_StatesCount];
    int             m_State;
    SEL             m_TargetSelector;
    id              m_Target;
}

- (BOOL)isFlipped;
- (void)calcSize;
- (void)setStateImg: (int)state withResourceImage:(NSString*)ResourceImgName withSize:(NSSize)size;
- (void)setState: (int)state;
- (void)mouseUp:(NSEvent *)theEvent;
- (void)setAction:(SEL)aSelector;
- (void)setTarget:(id)anObject;
- (void)dealloc;

@end
