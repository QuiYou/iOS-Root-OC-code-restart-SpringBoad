//  ----------------------------------------------------------------------
//  Copyright (C) 2018 诚怀网络（110.com）- 诚怀网络开发者社区.
//  All rights reserved.
//  Site URL:  http://110.com
//
//  110.com PROPRIETARY/CONFIDENTIAL. Use is subject to license terms.
//
//  You can contact author with aso2001@foxmail.com or 2578254536@qq.com.
//  ----------------------------------------------------------------------
//
//
//  Created by laote on 2023/10/17.
//  Copyright © 2023 Mr.Laote. All rights reserved.
//

#import <Foundation/NSObject.h>
 
@class NSString, NSArray, NSDictionary;
 
@interface NSTask : NSObject
 
// Create an NSTask which can be run at a later time
// An NSTask can only be run once. Subsequent attempts to
// run an NSTask will raise.
// Upon task death a notification will be sent
//   { Name = NSTaskDidTerminateNotification; object = task; }
//
 
- (instancetype)init;
 
// set parameters
// these methods can only be done before a launch
// if not set, use current
// if not set, use current
 
// set standard I/O channels; may be either an NSFileHandle or an NSPipe
- (void)setStandardInput:(id)input;
- (void)setStandardOutput:(id)output;
- (void)setStandardError:(id)error;
 
// get parameters
@property (NS_NONATOMIC_IOSONLY, copy) NSString *launchPath;
@property (NS_NONATOMIC_IOSONLY, copy) NSArray *arguments;
@property (NS_NONATOMIC_IOSONLY, copy) NSDictionary *environment;
@property (NS_NONATOMIC_IOSONLY, copy) NSString *currentDirectoryPath;
 
// get standard I/O channels; could be either an NSFileHandle or an NSPipe
- (id)standardInput;
- (id)standardOutput;
- (id)standardError;
 
// actions
- (void)launch;
 
- (void)interrupt; // Not always possible. Sends SIGINT.
- (void)terminate; // Not always possible. Sends SIGTERM.
 
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL suspend;
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL resume;
 
// status
@property (NS_NONATOMIC_IOSONLY, readonly) int processIdentifier;
@property (NS_NONATOMIC_IOSONLY, getter = isRunning, readonly) BOOL running;
 
@property (NS_NONATOMIC_IOSONLY, readonly) int terminationStatus;
 
@end
 
@interface NSTask (NSTaskConveniences)
 
+ (NSTask *)launchedTaskWithLaunchPath:(NSString *)path arguments:(NSArray *)arguments;
// convenience; create and launch
 
- (void)waitUntilExit;
// poll the runLoop in defaultMode until task completes
 
@end
 
FOUNDATION_EXPORT NSString * const NSTaskDidTerminateNotification;
