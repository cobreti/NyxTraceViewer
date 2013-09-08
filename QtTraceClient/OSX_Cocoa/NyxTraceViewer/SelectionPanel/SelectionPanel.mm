//
//  SelectionPanel.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-09-07.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "SelectionPanel.h"
#import "SelectionPanelBar.h"
#import "SourcesView/SourcesView.h"

@implementation CSelectionPanel

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        
        m_Bar = [[CSelectionPanelBar alloc] initWithFrame: NSMakeRect(0, 0, 200,50)];
        [m_Bar setPanelSelectionChangedHandler: CActionHandlerInfo(@selector(onPanelSelectionChanged:), self)];
        [self addSubview: m_Bar];
        
        m_SourcesView = [[CSourcesView alloc] initWithFrame: NSMakeRect(0, 50, 200, 400)];
        [self addSubview: m_SourcesView];
        [m_SourcesView setHidden: NO];
        
        [m_Bar calcSize];

        m_SourcesView.translatesAutoresizingMaskIntoConstraints = NO;
        m_Bar.translatesAutoresizingMaskIntoConstraints = NO;
        
        [self addConstraint: [NSLayoutConstraint constraintWithItem: m_Bar
                                                          attribute: NSLayoutAttributeTop
                                                          relatedBy: NSLayoutRelationEqual
                                                             toItem: self
                                                          attribute: NSLayoutAttributeTop
                                                         multiplier: 1
                                                           constant: 0 ]];

        [self addConstraint: [NSLayoutConstraint constraintWithItem: m_Bar
                                                          attribute: NSLayoutAttributeWidth
                                                          relatedBy: NSLayoutRelationEqual
                                                             toItem: self
                                                          attribute: NSLayoutAttributeWidth
                                                         multiplier: 1
                                                           constant: 10 ]];

        [self addConstraint: [NSLayoutConstraint constraintWithItem: m_SourcesView
                                                          attribute: NSLayoutAttributeTop
                                                          relatedBy: NSLayoutRelationEqual
                                                             toItem: m_Bar
                                                          attribute: NSLayoutAttributeBottom
                                                         multiplier: 1
                                                           constant: 0 ]];
        
        [self addConstraint: [NSLayoutConstraint constraintWithItem: m_SourcesView
                                                          attribute: NSLayoutAttributeBottom
                                                          relatedBy: NSLayoutRelationEqual
                                                             toItem: self
                                                          attribute: NSLayoutAttributeBottom
                                                         multiplier: 1
                                                           constant: 0 ]];

        [self addConstraint: [NSLayoutConstraint constraintWithItem: m_SourcesView
                                                          attribute: NSLayoutAttributeLeft
                                                          relatedBy: NSLayoutRelationEqual
                                                             toItem: self
                                                          attribute: NSLayoutAttributeLeft
                                                         multiplier: 1
                                                           constant: 0 ]];

        [self addConstraint: [NSLayoutConstraint constraintWithItem: m_SourcesView
                                                          attribute: NSLayoutAttributeWidth
                                                          relatedBy: NSLayoutRelationEqual
                                                             toItem: self
                                                          attribute: NSLayoutAttributeWidth
                                                         multiplier: 1
                                                           constant: 0 ]];

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

- (IBAction)onPanelSelectionChanged:(id)sender
{
    int panelId = [m_Bar selectedPanel];
    
    switch (panelId)
    {
        case kSelectionPanelBar_SourcesPanel:
            {
                [m_SourcesView setHidden: NO];
            }
            break;
        case kSelectionPanelBar_ChannelsPanel:
            {
                [m_SourcesView setHidden: YES];
            }
            break;
    };
}

- (void)drawRect:(NSRect)dirtyRect
{
    // Drawing code here.
}

@end
