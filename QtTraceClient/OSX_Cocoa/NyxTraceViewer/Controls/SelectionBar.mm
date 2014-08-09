//
//  SelectionBar.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-07.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "SelectionBar.h"
#import "ToggleFlatBtn.h"

#include <Nyx.hpp>

enum {    
    kTopMargin = 5,
    kBottomMargin = 5,
    kInterBtnSpace = 10
};

@implementation CSelectionBar


- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}


- (void)drawRect:(NSRect)dirtyRect
{
    // Drawing code here.
}

- (void)addBtn: (CToggleFlatBtn*)btn
{
    [self addSubview: btn];
    
    btn.translatesAutoresizingMaskIntoConstraints = NO;

    [btn setSelectedActionHandler: CActionHandlerInfo(@selector(onBtnClicked:), self) ];
    
    [self addConstraint: [NSLayoutConstraint constraintWithItem:btn
                                                      attribute: NSLayoutAttributeTop
                                                      relatedBy: NSLayoutRelationEqual
                                                         toItem: self
                                                      attribute: NSLayoutAttributeTop
                                                     multiplier: 0
                                                       constant: kTopMargin ]];

    if ( m_Btns.size() > 0 ) {

        CToggleFlatBtn*     pLeftBtn = m_Btns[m_Btns.size()-1];
        
        [self addConstraint: [NSLayoutConstraint constraintWithItem:btn
                                                          attribute: NSLayoutAttributeLeft
                                                          relatedBy: NSLayoutRelationEqual
                                                             toItem: pLeftBtn
                                                          attribute: NSLayoutAttributeRight
                                                         multiplier: 1
                                                           constant: 22 ]];
    }
    else
    {
        [self addConstraint: [NSLayoutConstraint constraintWithItem:btn
                                                          attribute: NSLayoutAttributeLeft
                                                          relatedBy: NSLayoutRelationEqual
                                                             toItem: self
                                                          attribute: NSLayoutAttributeLeft
                                                         multiplier: 0
                                                           constant: 0 ]];
    }
    
    m_Btns.push_back(btn);   
}


- (CToggleFlatBtn*)activeBtn
{
    CToggleFlatBtn* pBtn = NULL;

    int index = 0;
    while (index < m_Btns.size())
    {
        if ( [m_Btns[index] state] == kToggleFlatBtn_OnState )
        {
            pBtn = m_Btns[index];
            break;
        }
            
        ++ index;
    }
    
    return pBtn;
}


- (void)calcSize
{
    NSSize  btnSize;
    NSSize  rowSize = NSZeroSize;
    
    TBtnsVector::const_iterator      pos = m_Btns.begin();
    
    while (pos != m_Btns.end())
    {
        CToggleFlatBtn* pBtn = *pos;
        
        [pBtn calcSize];
        btnSize = [pBtn frame].size;
        
        rowSize.height = MAX(rowSize.height, btnSize.height);
        rowSize.width += btnSize.width + kInterBtnSpace;
        
        ++ pos;
    }
    
    [self setFrame: NSMakeRect(0, 0, rowSize.width, rowSize.height + kTopMargin + kBottomMargin)];
}


- (BOOL)isFlipped
{
    return YES;
}


- (NSSize) intrinsicContentSize
{
    return [self frame].size;
}

- (void)onBtnClicked: (id)sender
{
    TBtnsVector::const_iterator     pos = m_Btns.begin();
    
    while (pos != m_Btns.end())
    {
        if ( sender != *pos)
        {
            [*pos setState: kToggleFlatBtn_OffState];
        }
        ++ pos;
    }
    
    if (m_BtnSelectionChangedHandler.Valid())
        [self sendAction: m_BtnSelectionChangedHandler.Selector() to:m_BtnSelectionChangedHandler.Target()];
}

- (void)dealloc
{
    TBtnsVector::const_iterator     pos = m_Btns.begin();
    
    while (pos != m_Btns.end())
    {
        [*pos release];
        ++ pos;
    }
    
    [super dealloc];
}


- (void)setBtnSelectionChangedHandler: (const CActionHandlerInfo&)handler
{
    m_BtnSelectionChangedHandler = handler;
}


@end

