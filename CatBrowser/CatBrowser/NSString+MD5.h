//
//  NSString+MD5.h
//  CatBrowser
//
//  Created by Vincent Le Quang on 4/5/14.
//  Copyright (c) 2014 Dobuki Studio. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (MD5)
- (NSString *)md5;
@end

@interface NSData (MD5)
- (NSString *)md5;
@end
