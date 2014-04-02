//
//  CatURLProtocol.m
//  CatBrowser
//
//  Created by Vincent Le Quang on 4/2/14.
//  Copyright (c) 2014 Dobuki Studio. All rights reserved.
//

#import "CatURLProtocol.h"

@implementation CatURLProtocol
{
    NSMutableURLRequest* catRequest;
}


+ (BOOL)canInitWithRequest:(NSURLRequest *)request {
    
    NSString *fileExtension = request.URL.pathExtension;
    NSString *scheme = request.URL.scheme;
    if([fileExtension isEqualToString:@"jpg"]
       || [fileExtension isEqualToString:@"png"]
       || [fileExtension isEqualToString:@"gif"]
        || [fileExtension isEqualToString:@"jpeg"]
        || [fileExtension isEqualToString:@"bmp"]
            || [scheme isEqualToString:@"data"]
            || [scheme isEqualToString:@"data:image/"]
            || [request.URL.absoluteString rangeOfString:@"https://encrypted-tbn"].location!=NSNotFound)
    {
        return ![[[request allHTTPHeaderFields] objectForKey:@"BANANA"] isEqualToString:@"APPLE"];
    }
    return NO;
}

+ (NSURLRequest *)canonicalRequestForRequest:(NSURLRequest *)request {
    return request;
}



@end
