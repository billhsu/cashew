//
//  ChooseMirrorWindowController.m
//  cashew
//
//  Created by Xu, Shipeng on 19/7/15.
//  Copyright (c) 2015 Xu, Shipeng. All rights reserved.
//

#import "ChooseMirrorWindowController.h"

@implementation ChooseMirrorWindowController
@synthesize selectedIndex;
- (IBAction)onOK:(id)sender {
    [NSApp stopModal];
    [[self window]orderOut: nil];
    
    [[NSApplication sharedApplication] endSheet:[self window] returnCode:NSOKButton];
}
@end