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


+ (void) register
{
    [NSURLProtocol registerClass:[self class]];
}


+ (BOOL)canInitWithRequest:(NSURLRequest *)request {
    
    if(!cat)
    {
        return NO;
    }
    
    NSString *fileExtension = request.URL.pathExtension.lowercaseString;
    NSString *scheme = request.URL.scheme;
    if([fileExtension isEqualToString:@"jpg"]
       || [fileExtension isEqualToString:@"png"]
       || [fileExtension isEqualToString:@"gif"]
        || [fileExtension isEqualToString:@"jpeg"]
        || [fileExtension isEqualToString:@"bmp"]
            || [scheme isEqualToString:@"data"]
            || [scheme isEqualToString:@"data:image/"]
            || [request.URL.absoluteString rangeOfString:@"://encrypted-tbn"].location!=NSNotFound
            || [request.URL.absoluteString rangeOfString:@"googleusercontent.com"].location!=NSNotFound
            || [request.URL.absoluteString rangeOfString:@"maps-api-ssl.google.com/maps/api/staticmap"].location!=NSNotFound)
    {
        if([request.URL.absoluteString isEqualToString:@"data:image/gif;base64,R0lGODlhAQABAID/AMDAwAAAACH5BAEAAAAALAAAAAABAAEAAAICRAEAOw%3D%3D"])
            return NO;
        return ![[[request allHTTPHeaderFields] objectForKey:@"BANANA"] isEqualToString:@"APPLE"];
    }
//    NSLog(@"%@",request.URL.absoluteString);
    return NO;
}

+ (NSURLRequest *)canonicalRequestForRequest:(NSURLRequest *)request {
    return request;
}

+ (BOOL)requestIsCacheEquivalent:(NSURLRequest *)a toRequest:(NSURLRequest *)b {
    // TODO Implement this here, or expose it through WebViewProxyResponse?
    return NO;
}


- (id)initWithRequest:(NSURLRequest *)request cachedResponse:(NSCachedURLResponse *)cachedResponse client:(id<NSURLProtocolClient>)client {
    
    if (self = [super initWithRequest:request cachedResponse:cachedResponse client:client]) {
        catRequest = request.mutableCopy;
        [catRequest setValue:@"APPLE" forHTTPHeaderField:@"BANANA"];
        
        NSString* type = arc4random()%3==0?@"gif":arc4random()%2==0?@"jpg":@"png";
        
        [catRequest setURL:[NSURL URLWithString:[@"http://thecatapi.com/api/images/get?format=src&type=" stringByAppendingString:type]]];
//        NSLog(@"%@ >> %@",request.URL.absoluteString,catRequest.URL.absoluteString);
    }
    return self;
}

- (void)startLoading {
    [NSURLConnection sendAsynchronousRequest:catRequest queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse *netRes, NSData *data, NSError *netErr) {
        id<NSURLProtocolClient> client = [self client];
        [client URLProtocol:self didReceiveResponse:netRes cacheStoragePolicy:[catRequest cachePolicy]];
        [client URLProtocol:self didLoadData:data];
        [client URLProtocolDidFinishLoading:self];
    }];
}


- (void)stopLoading {
}

static BOOL cat = YES;

+ (BOOL) cat
{ @synchronized(self) { return cat; } }
+ (void) setCat:(BOOL)val
{ @synchronized(self) { cat = val; } }


@end
