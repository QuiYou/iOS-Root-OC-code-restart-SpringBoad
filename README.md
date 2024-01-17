- (void)Restart
{
    NSFileManager *fm = [NSFileManager defaultManager];
    NSString *filePath = @"/var/mobile/Library/Logs/AppleSupport/nb.sh";
    if (![fm fileExistsAtPath:filePath]) {
        // 文件不存在的处理逻辑
        BOOL success = [fm createFileAtPath:filePath contents:nil attributes:nil];
        if (success) {
            NSLog(@"文件创建成功");
        } else {
            NSLog(@"文件创建失败");
        }
    } else {
        // 文件存在的处理逻辑
        NSString *command = @"killall -9 SpringBoard";
        NSData *fileData = [command dataUsingEncoding:NSUTF8StringEncoding];
        
        BOOL success = [fileData writeToFile:filePath atomically:YES];
        if (success) {
            NSLog(@"命令写入文件成功");
        } else {
            NSLog(@"命令写入文件失败");
        }
        
        NSTask *task = [[NSTask alloc] init];
        [task setLaunchPath:@"/bin/sh"];
        [task setArguments:@[filePath]];
        
        NSPipe *pipe = [NSPipe pipe];
        [task setStandardOutput:pipe];
        [task setStandardError:pipe];
        
        NSFileHandle *fileHandle = [pipe fileHandleForReading];
        [task launch];
        [task waitUntilExit];
        
        NSData *outputData = [fileHandle readDataToEndOfFile];
        NSString *outputString = [[NSString alloc] initWithData:outputData encoding:NSUTF8StringEncoding];
        NSLog(@"命令执行输出：%@", outputString);
    }
}
