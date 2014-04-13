#import "PIOError.h"

/**
 The Player.IO GameFS service.
 */
@interface PIOGameFS : NSObject{
    @private
    NSString* gameId;
    NSMutableDictionary* maps;
}

/**
 * Converts a GameFS path (like '/mygame.swf') into a full url, that can be downloaded over the internet.
 * Important! Do not save or otherwise persist (bigdb, cookies, etc) the returned url, since the url will change over time.
 * @param path The path of the file in the GameFS, including the initial slash. Examples: '/mygame.swf' or '/characters/bob.jpg'
 * @returns An url that can be used to download the resource over the internet.
 */
- (NSString*) getUrlWithPath:(NSString*)path;

/**
 * Converts a GameFS path (like '/mygame.swf') into a full url, that can be downloaded over the internet.
 * Important! Do not save or otherwise persist (bigdb, cookies, etc) the returned url, since the url will change over time.
 * @param path The path of the file in the GameFS, including the initial slash. Examples: '/mygame.swf' or '/characters/bob.jpg'
 * @param useSecureHttp If true, this method returns a secure (https) url.
 * @returns An url that can be used to download the resource over the internet.
 */
- (NSString*) getUrlWithPath:(NSString*)path useSecureHttp:(bool)useSecureHttp;

/**
 * Download a GameFS file, using the default shared NSUrlCache.
 * An application with more specific needs can create a custom NSURLCache object and set it as the shared cache instance using [NSUrlCache setSharedURLCache:]. The application should do so before any calls to this method.
 * @param path The path of the file in the GameFS, including the initial slash. Examples: '/mygame.swf' or '/characters/bob.jpg'
 * @param useSecureHttp If true, this method returns a secure (https) url.
 * @param timeout The time to wait for response before the errorBlock is called
 * @param progressBlock Called intermittently during download with the current progress of the download
 * @param successBlock A callback block that will be called with the downloaded data
 * @param errorBlock A callback block that will be called on error, with information about the error.
 */
- (void) downloadPath:(NSString*)path useSecureHttp:(bool)useSecureHttp timeout:(NSTimeInterval)timeout progressBlock:(void (^)(float progress))progressBlock successBlock:(void (^)(NSData* data))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

/**
 * Download a GameFS file to disk, using the default shared NSUrlCache.
 * An application with more specific needs can create a custom NSURLCache object and set it as the shared cache instance using [NSUrlCache setSharedURLCache:]. The application should do so before any calls to this method.
 * @param path The path of the file in the GameFS, including the initial slash. Examples: '/mygame.swf' or '/characters/bob.jpg'
 * @param filePath the path on disk to save the file to.
 * @param useSecureHttp If true, this method returns a secure (https) url.
 * @param timeout The time to wait for response before the errorBlock is called
 * @param progressBlock Called intermittently during download with the current progress of the download
 * @param successBlock A callback block that will be called with the downloaded data
 * @param errorBlock A callback block that will be called on error, with information about the error.
 */
- (void) downloadPath:(NSString*)path toFile:(NSString*)filePath  useSecureHttp:(bool)useSecureHttp timeout:(NSTimeInterval)timeout progressBlock:(void (^)(float progress))progressBlock successBlock:(void (^)(NSString* filePath))successBlock errorBlock:(void (^)(PIOError* error))errorBlock;

@end
