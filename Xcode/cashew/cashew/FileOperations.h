//
//  FileOperations.h
//  cashew
//
//  Created by Xu, Shipeng on 28/3/15.
//  Copyright (c) 2015 Xu, Shipeng. All rights reserved.
//

#ifndef cashew_FileOperations_h
#define cashew_FileOperations_h
#import "FileOperationsCppWrapper.h"
#include <iostream>
@interface FileOperations : NSObject {
}
-(std::string) showSaveFileDialog;
-(std::string) showOpenFileDialog;
-(std::string) showNewFileDialog;
@end
#endif
