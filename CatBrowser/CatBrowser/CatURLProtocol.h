//
//  CatURLProtocol.h
//  CatBrowser
//
//  Created by Vincent Le Quang on 4/2/14.
//  Copyright (c) 2014 Dobuki Studio. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CatURLProtocol : NSURLProtocol
+ (void) register;

+ (BOOL) cat;
+ (void) setCat:(BOOL)val;

@end
