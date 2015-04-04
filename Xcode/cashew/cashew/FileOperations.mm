//
//  FileOperations.m
//  cashew
//
//  Created by Xu, Shipeng on 28/3/15.
//  Copyright (c) 2015 Xu, Shipeng. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "FileOperations.h"
#import <AppKit/AppKit.h>
#include <iostream>

@implementation FileOperations
std::string showSaveFileDialogWrapper (void *self) {
    return [(__bridge id) self showSaveFileDialog];
}

-(std::string) showSaveFileDialog {
    // create the save panel
    NSSavePanel *panel = [NSSavePanel savePanel];
    
    // set a new file name
    [panel setNameFieldStringValue:@"NewFile.cashew"];
    std::string filePath = "";
    // display the panel
    NSInteger result = [panel runModal];
    if(result == NSOKButton) {
        NSString *saveURL = [[panel URL] path];
        filePath = std::string([saveURL UTF8String]);
    }
    return filePath;
}

std::string showOpenFileDialogWrapper (void *self) {
    return [(__bridge id) self showOpenFileDialog];
}

-(std::string) showOpenFileDialog {
    // create the open panel
    NSOpenPanel *panel = [NSOpenPanel openPanel];
    
    std::string filePath = "";
    // display the panel
    NSInteger result = [panel runModal];
    if(result == NSOKButton) {
        NSString *openURL = [[panel URL] path];
        filePath = std::string([openURL UTF8String]);
    }
    return filePath;
}

std::string showNewFileDialogWrapper (void *self) {
    return [(__bridge id) self showNewFileDialog];
}

-(std::string) showNewFileDialog {
    NSAlert *alert = [[NSAlert alloc] init];
    
    [alert addButtonWithTitle:@"OK"];
    
    [alert addButtonWithTitle:@"Cancel"];
    
    [alert setMessageText:@"Create a new sketch?"];
    
    [alert setInformativeText:@"Current sktech will be discarded."];
    
    [alert setAlertStyle:NSWarningAlertStyle];
    if ([alert runModal] == NSAlertFirstButtonReturn) {
        return "OK";
    } else {
        return "CANCEL";
    }
    
}
@end