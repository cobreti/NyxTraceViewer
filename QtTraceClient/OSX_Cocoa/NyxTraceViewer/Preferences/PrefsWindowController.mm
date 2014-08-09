//
//  PrefsControllerWindowController.m
//  NyxTraceViewer
//
//  Created by Danny Thibaudeau on 2013-10-19.
//  Copyright (c) 2013 Danny Thibaudeau. All rights reserved.
//

#import "PrefsWindowController.h"

@interface PrefsWindowController ()

@end

@implementation PrefsWindowController

- (id)initWithWindow:(NSWindow *)window
{
    self = [super initWithWindow:window];
    if (self) {
        
        m_pConnectionSettingsView = NULL;
        m_pScrollView = NULL;
    }
    return self;
}


- (void)windowDidLoad
{
    [super windowDidLoad];
    
    [self CreateConnectionSettingsView];
}

- (IBAction)showWindow:(id)sender
{
    [super showWindow: sender];
    
    [[self prefsWindow] makeKeyAndOrderFront:nil];
}


- (void) CreateConnectionSettingsView
{
    
    NSView* contentView = [[self prefsWindow] contentView];
    
    m_pConnectionSettingsView = [[CConnectionSettingsView alloc] init];
    [m_pConnectionSettingsView setHidden: NO];
    
    m_pScrollView = [[NSScrollView alloc] init];
    
    m_pScrollView.translatesAutoresizingMaskIntoConstraints = NO;
    
    [contentView addSubview: m_pScrollView];

    [contentView addConstraint: [NSLayoutConstraint constraintWithItem: m_pScrollView
                                                      attribute: NSLayoutAttributeWidth
                                                      relatedBy: NSLayoutRelationEqual
                                                         toItem: contentView
                                                      attribute: NSLayoutAttributeWidth
                                                     multiplier: 1
                                                       constant: 0 ]];

    [contentView addConstraint: [NSLayoutConstraint constraintWithItem: m_pScrollView
                                                             attribute: NSLayoutAttributeHeight
                                                             relatedBy: NSLayoutRelationEqual
                                                                toItem: contentView
                                                             attribute: NSLayoutAttributeHeight
                                                            multiplier: 1
                                                              constant: 0 ]];

    [contentView addConstraint: [NSLayoutConstraint constraintWithItem: m_pScrollView
                                                             attribute: NSLayoutAttributeLeft
                                                             relatedBy: NSLayoutRelationEqual
                                                                toItem: contentView
                                                             attribute: NSLayoutAttributeLeft
                                                            multiplier: 0
                                                              constant: 0 ]];

    [contentView addConstraint: [NSLayoutConstraint constraintWithItem: m_pScrollView
                                                             attribute: NSLayoutAttributeTop
                                                             relatedBy: NSLayoutRelationEqual
                                                                toItem: contentView
                                                             attribute: NSLayoutAttributeTop
                                                            multiplier: 0
                                                              constant: 0 ]];

    [m_pScrollView setDocumentView: m_pConnectionSettingsView];
    [m_pScrollView setHasVerticalScroller:YES];
}

@end

