//
//  SelectionPanel.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-07.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "SelectionPanel.h"
#import "SelectionPanelBar.h"

@implementation CSelectionPanel

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        
        m_Bar = [[CSelectionPanelBar alloc] initWithFrame: NSMakeRect(0, 0, 200,50)];
        [self addSubview: m_Bar];
        
        [m_Bar calcSize];
//        [m_Bar setAutoresizingMask: NSViewWidthSizable];

        m_Bar.translatesAutoresizingMaskIntoConstraints = NO;
        
        [self addConstraint: [NSLayoutConstraint constraintWithItem: m_Bar
                                                          attribute: NSLayoutAttributeWidth
                                                          relatedBy: NSLayoutRelationEqual
                                                             toItem: self
                                                          attribute: NSLayoutAttributeWidth
                                                         multiplier: 1
                                                           constant: 10 ]];

//        [self addConstraint: [NSLayoutConstraint constraintWithItem: m_Bar
//                                                          attribute: NSLayoutAttributeLeft
//                                                          relatedBy: NSLayoutRelationEqual
//                                                             toItem: self
//                                                          attribute: NSLayoutAttributeLeft
//                                                         multiplier: 1
//                                                           constant: 10 ]];

//        [self addConstraint: [NSLayoutConstraint constraintWithItem: self
//                                                          attribute: NSLayoutAttributeWidth
//                                                          relatedBy: NSLayoutRelationEqual
//                                                             toItem: m_Bar
//                                                          attribute: NSLayoutAttributeWidth
//                                                         multiplier: 1
//                                                           constant: 0 ]];

//        [self addConstraints:[NSLayoutConstraint
//                                   constraintsWithVisualFormat:@"V:|[m_Bar]" // 80 height
//                                options:0 metrics:nil views:NSDictionaryOfVariableBindings(m_Bar)]];
//        [self addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"H:|[m_Bar(==self)]"
//                                     options:0 metrics:nil views:NSDictionaryOfVariableBindings(m_Bar, self)]];
    }
    
    return self;
}

- (BOOL) isFlipped
{
    return YES;
}

- (void) dealloc
{
    [m_Bar release];
    
    [super dealloc];
}

- (void)drawRect:(NSRect)dirtyRect
{
    // Drawing code here.
}

@end
